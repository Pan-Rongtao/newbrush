#include "catch2/catch.hpp"
#include "newbrush/Application.h"
#include "newbrush/NBBParser.h"
#include "newbrush/Log.h"
#include "GLFW/glfw3.h"

using namespace nb;

class A
{
	RTTR_ENABLE()
};
class B : public A
{
	RTTR_ENABLE(A)
public:
	int x = 0;
};

class CCC
{
public:
	ref<A> bv;
};

RTTR_REGISTRATION
{
	registration::class_<A>("A")
	.constructor<>() (policy::ctor::as_std_shared_ptr)
	;

registration::class_<B>("B")
.constructor<>() (policy::ctor::as_std_shared_ptr)
.property("X", &B::x);
;

registration::class_<CCC>("CCC")
.constructor<>() (policy::ctor::as_std_shared_ptr)
.property("bv", &CCC::bv);
;

}

TEST_CASE("TestRTTR", "[TestRTTR]")
{
	auto tC = type::get_by_name("CCC");
	auto objC = tC.create();
	auto propertyC = tC.get_property("bv");

	ref<A> v;
	auto bd = std::make_shared<B>();
	bd->x = 10;
	v = bd;

	bool sucess = propertyC.set_value(objC, v);
	
	auto tB = type::get_by_name("B");
	auto objB = tB.create();
	auto tBB = objB.get_type();
	auto propertyB = tBB.get_wrapped_type().get_property("X");
	bool bpb = propertyB.set_value(objB, 11);
	/*
	instance ins = v;
	auto ttB = ins.get_wrapped_instance().get_derived_type();
	auto vx = ttB.create();

	vx = v;
	auto dd = vx.get_value<APtr>();
	//auto vvv = ttB.register_wrapper_converter_for_base_classes
	*/
	bool b = propertyC.set_value(objC, objB);
	int xx = 10;
}

TEST_CASE("TestNBBParser", "[TestNBBParser]")
{
	Window w;

	NBBParser parser;
	ref<Scene> scene;
	parser.parse("../resource/a08/a08.json", scene);

}

TEST_CASE("TestGlobalProperties", "[TestGlobalProperties]")
{
	bool b = addGlobalProperty<int>("IntProperty", 1);
	b = addGlobalProperty<int>("IntProperty", 1);
}

TEST_CASE("TestShader", "[TestShader]")
{
	Window w;

	const char *vsCode = R"(
		uniform mediump mat4    WorldViewProjection;
		uniform    mat4    LightWorldViewProjection;
		uniform mediump mat4	World;
		uniform mediump	 vec3	CamPos;

		varying mediump vec2	varCoord;
		varying lowp	vec3	varNormal;
		varying lowp	vec3	varTangent;
		varying lowp	vec3	varBinormal;
		varying mediump vec3	LightPos;
		varying mediump vec3	LightPos1;
		varying mediump vec3	WorldPos;
		varying mediump	vec3	camPos;
		varying highp	vec4	RasterPosbyLight;

		attribute highp  vec4	myVertex;
		attribute lowp	  vec3	myNormal;
		attribute lowp    vec3  myTanget;
		attribute lowp    vec3  myBinormal;
		attribute mediump vec2	myUV;

		void main(void)
		{

		gl_Position =  ( WorldViewProjection )*myVertex;

		RasterPosbyLight =  ( LightWorldViewProjection )*myVertex;

		lowp mat3 world = mat3(World);

		WorldPos = vec3(World * myVertex);

		varNormal = normalize(world * myNormal);
		varTangent = normalize(world * myTanget);
		varBinormal = normalize(world * myBinormal);

		//LightPos = myLightDirection;


		camPos = CamPos;

		varCoord = myUV.st;

		}
	)";
	const char *fgCode = R"(
		uniform sampler2D sampler2d;
		uniform sampler2D normal2d;
		uniform highp sampler2D shadow2d;

		uniform bool PCF;
		uniform mediump float ResShadowMap;

		uniform mediump	 vec3	CamPos;

		varying mediump  vec2	varCoord;
		varying lowp     vec3	varNormal;
		varying lowp     vec3	varTangent;
		varying lowp     vec3	varBinormal;
		varying mediump  vec3	WorldPos;
		uniform mediump vec3	myLightDirection;
		uniform mediump vec3	myLightDirection1;
		varying highp	vec4	RasterPosbyLight;

		highp float ComputeShadow(){
			highp  vec2 ShadowTC = 0.5 * RasterPosbyLight.xy / RasterPosbyLight.w + vec2(0.5,0.5);	
	
			if(ShadowTC.x > 1.0 || ShadowTC.y > 1.0 || ShadowTC.x  < 0.0 || ShadowTC.y < 0.0 || RasterPosbyLight.w < 0.0 )
			  return 1.0;
	  
			highp float depth = texture2D(shadow2d,ShadowTC).r*2.0 - 1.0;
			highp float distance = RasterPosbyLight.z/RasterPosbyLight.w;
			depth += 0.000005;
			if( distance > depth)
				return 0.5;

			return 1.0;
		}

		mediump float ComputeShadowPCF(){
			highp  vec2 ShadowTC = 0.5 * RasterPosbyLight.xy / RasterPosbyLight.w + vec2(0.5,0.5);	
	
			if(ShadowTC.x > 1.0 || ShadowTC.y > 1.0 || ShadowTC.x  < 0.0 || ShadowTC.y < 0.0 || RasterPosbyLight.w < 0.0 )
			  return 1.0;
	  
			mediump float radius = 3.0;
			mediump vec2 vTexCoords[9];
			mediump float fTexelSize = 1.0 / (ResShadowMap*radius);

			vTexCoords[0] = ShadowTC;
			vTexCoords[1] = ShadowTC + vec2( -fTexelSize, 0.0  );
			vTexCoords[2] = ShadowTC + vec2(  fTexelSize, 0.0  );
			vTexCoords[3] = ShadowTC + vec2( 0.0,        -fTexelSize );
			vTexCoords[6] = ShadowTC + vec2( 0.0,         fTexelSize );
			vTexCoords[4] = ShadowTC + vec2( -fTexelSize, -fTexelSize );
			vTexCoords[5] = ShadowTC + vec2(  fTexelSize, -fTexelSize );
			vTexCoords[7] = ShadowTC + vec2( -fTexelSize,  fTexelSize );
			vTexCoords[8] = ShadowTC + vec2(  fTexelSize,  fTexelSize );
	
			mediump float fShadowTerm = 0.0;
			for(int i=0; i<9; i++){
					if(RasterPosbyLight.z/RasterPosbyLight.w >= texture2D(shadow2d,vTexCoords[i]).r*2.0 - 1.0 + 0.00005)
						fShadowTerm += 0.2;
					else
						fShadowTerm += 1.0;
				}
		
			fShadowTerm /= 9.0;
 			return fShadowTerm;
		}

		void main (void)
		{
 			lowp  vec3 color = vec3(0.5,0.5,0.5); //vec3(texture2D(sampler2d,varCoord));
			/*mediump  vec3 N = vec3(texture2D(normal2d,varCoord));
 			N = (N*2.0) - 1.0;
 	
 			lowp  vec3 Nn = normalize(varNormal);
 			lowp  vec3 Tn = normalize(varTangent); //varTangent 
 			lowp  vec3 Bn = -normalize(varBinormal);  //varBinormal
 	
 			lowp mat3 TBN = mat3(Tn,Bn,Nn);
 	
 			lowp  vec3 normal = TBN*N;
 	
 			normal = normalize(normal);
			*/
			lowp  vec3 normal = normalize(varNormal);
 	
 			mediump vec3 lightsPos[2];
 			lightsPos[0] = myLightDirection;
 			lightsPos[1] = myLightDirection1;
 			lowp vec3 eyeDir = normalize(CamPos - WorldPos);
 	
 			lowp  vec3 totaldiffuse =  vec3(0.0,0.0,0.0);
 			lowp  vec3 totalspecular = vec3(0.0,0.0,0.0);
 	 
 			for(int i=0;i<2;i++){ 	
 			lowp vec3 lightvec =  normalize(lightsPos[i] - WorldPos);
 			lowp float lambert = max(dot(lightvec,normal),0.0);
 			lambert*=0.5;
 			lowp vec3 floatvector = normalize(eyeDir+lightvec); 
 			lowp float specular;
 			lowp vec3 Specular = vec3(1.0,1.0,1.0);
 			specular = max(dot(floatvector, normal),0.0); 
 			specular = pow(specular, 100.0); 
 			specular *= lambert; 
 			Specular *= specular;
 	
 			totaldiffuse+=lambert;
 			totalspecular+=0.5*Specular;
 			}
 	
 			color*=totaldiffuse;
 			color+=totalspecular;
 	
 			gl_FragColor = vec4( color, 1.0);		
	 

		}
	)";

}

TEST_CASE("TestGLFW", "[TestGLFW]")
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 32);
	//glEnable(GL_MULTISAMPLE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwWaitEvents();//检查事件
		glfwSwapBuffers(window);
	}
}


TEST_CASE("TestTimer", "[TestTimer]")
{
	Timer t(0, true);
	t.Tick += [](const EventArgs &e)
	{
		Log::info("tick");
	};
	t.start();

	while (true)
	{
		Timer::driveInLoop();
	}
}