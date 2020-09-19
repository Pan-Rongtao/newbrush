#include "newbrush/model/Bitmap.h"
#include "catch2/catch.hpp"
#include "Window.h"
#include "GLFW/glfw3.h"
#include <GLES2/gl2.h>
#include "newbrush/model/Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "newbrush/model/Camera.h"

using namespace nb;

MeshPtr processMesh(aiMesh * mesh, const aiScene * scene, const std::string &picPath)
{
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
	PhongMaterialPtr ma;
#ifdef WIN32
	for (int i = 0; i != mesh->mNumVertices; ++i)
	{
		Vertex ver;
		if (mesh->HasPositions())		ver.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		if (mesh->mColors[0])			ver.color = { mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a };
		if (mesh->mTextureCoords[0])	ver.texCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		if (mesh->HasNormals())			ver.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		vertexs.push_back(ver);
	}

	for (int i = 0; i != mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j != face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	static auto loadMaterialTextures = [&](aiMaterial *mat, aiTextureType type, int samplerUnit)->std::vector<TextureMipmapPtr> {
		std::vector<TextureMipmapPtr> textures;
		int ii = mat->GetTextureCount(type);
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type, i, &str);

			std::string filename = std::string(str.C_Str());
			filename = picPath + "/" + filename.substr(filename.find_last_of('\\') + 1);

			Bitmap bm(filename);
			auto textureMipPtr = std::make_shared<TextureMipmap>();
			auto glFormatAndType = Texture::getGlFormatAndType(bm.channels());
			textureMipPtr->update(bm.data(), bm.width(), bm.height(), glFormatAndType.first, glFormatAndType.second);
		//	textureMipPtr->setWrapping(TextureWrapping{ TextureWrapping::WrappingModeE::Repeat, TextureWrapping::WrappingModeE::Repeat });
		//	textureMipPtr->setFilter(TextureFilter{ TextureFilter::FilterE::Bilinear , TextureFilter::FilterE::Trilinear });
			textureMipPtr->setSamplerUnit(samplerUnit);

			textures.push_back(textureMipPtr);
		}
		return textures;
	};

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiColor3D ambient, diffuse, specular;
		auto materialName = material->GetName();
		aiString vsCode, fgCode;
		auto x = material->Get(AI_MATKEY_SHADER_VERTEX, vsCode);
		auto y = material->Get(AI_MATKEY_SHADER_FRAGMENT, fgCode);
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
		ma = std::make_shared<PhongMaterial>();
		ma->setAmbient(Color::fromRgbF(ambient.r, ambient.g, ambient.b));
		ma->setDiffuse(Color::fromRgbF(diffuse.r, diffuse.g, diffuse.b));
		ma->setSpecular(Color::fromRgbF(specular.r, specular.g, specular.b));

		// 1. diffuse maps
/*		auto diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, GL_TEXTURE0);
		ma->textures().insert(ma->textures().end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		auto specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, GL_TEXTURE1);
		//ma->textures().insert(ma->textures().end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		auto normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, GL_TEXTURE2);
		//ma->textures().insert(ma->textures().end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		auto heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, GL_TEXTURE3);
		//ma->textures().insert(ma->textures().end(), heightMaps.begin(), heightMaps.end());*/
	}

#endif
	return std::make_shared<Mesh>(vertexs, indices, ma);
}

void loopNode(aiNode * node, const aiScene * scene, const std::string &picPath, std::vector<MeshPtr> &meshes)
{
	static auto mat4_from_aimatrix4x4 = [](aiMatrix4x4 matrix) -> glm::mat4 {
		glm::mat4 res;
		for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) res[j][i] = matrix[i][j];
		return res;
	};

	for (int i = 0; i != node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		auto localMesh = processMesh(mesh, scene, picPath);
		localMesh->matrix = mat4_from_aimatrix4x4(node->mTransformation);
		meshes.push_back(localMesh);
	}
	for (int i = 0; i != node->mNumChildren; ++i)
		loopNode(node->mChildren[i], scene, picPath, meshes);
}

std::vector<MeshPtr> load(const std::string & path, const std::string &picPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("load [%s] fail:%s", path.data(), importer.GetErrorString());
		return{};
	}

	std::vector<MeshPtr> meshes;
	loopNode(scene->mRootNode, scene, picPath, meshes);
	return meshes;
}

TEST_CASE("test Renderer", "[Renderer]") {

	const GLuint WIDTH = 800, HEIGHT = 600;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, WIDTH, HEIGHT);

	auto meshes = load("../model/car.fbx", "../model");

	auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f, glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	glm::mat4 model = glm::mat4(1.0f);

	float strength{ 0.015f };
	model = glm::scale(model, glm::vec3(strength, strength, strength));
	model = glm::rotate(model, (GLfloat)glfwGetTime()*0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

	for (int i = 0; i != meshes.size(); ++i)
	{
		auto mesh = meshes[i];
		auto mat = model * mesh->matrix;
		mesh->matrix = mat;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i != meshes.size(); ++i)
		{
			auto mesh = meshes[i];
			mesh->draw(camera, {});
		}

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}