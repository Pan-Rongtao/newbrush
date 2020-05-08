#include "Node.grpc.pb.h"
#include "StubBase.h"

using namespace nbrpc;

class NodeStub : public NodeRpc::Service, public StubBase
{
	Status AddNode(ServerContext* context, const AddNodeRequest* request, CommonReply* response);
	Status RemoveNode(ServerContext* context, const RemoveNodeRequest* request, CommonReply* response);
	Status RenameNode(ServerContext* context, const RenameNodeRequest* request, CommonReply* response);
	Status SetPropertyBool(ServerContext* context, const SetPropertyBoolRequest* request, CommonReply* response);
	Status SetPropertyInt8(ServerContext* context, const SetPropertyInt8Request* request, CommonReply* response);
	Status SetPropertyInt16(ServerContext* context, const SetPropertyInt16Request* request, CommonReply* response);
	Status SetPropertyInt32(ServerContext* context, const SetPropertyInt32Request* request, CommonReply* response);
	Status SetPropertyInt64(ServerContext* context, const SetPropertyInt64Request* request, CommonReply* response);
	Status SetPropertyUInt8(ServerContext* context, const SetPropertyUInt8Request* request, CommonReply* response);
	Status SetPropertyUInt16(ServerContext* context, const SetPropertyUInt16Request* request, CommonReply* response);
	Status SetPropertyUInt32(ServerContext* context, const SetPropertyUInt32Request* request, CommonReply* response);
	Status SetPropertyUInt64(ServerContext* context, const SetPropertyUInt64Request* request, CommonReply* response);
	Status SetPropertyFloat(ServerContext* context, const SetPropertyFloatRequest* request, CommonReply* response);
	Status SetPropertyDouble(ServerContext* context, const SetPropertyDoubleRequest* request, CommonReply* response);
	Status SetPropertyString(ServerContext* context, const SetPropertyStringRequest* request, CommonReply* response);
	Status SetPropertyVec2(ServerContext* context, const SetPropertyVec2Request* request, CommonReply* response);
	Status SetPropertyVec3(ServerContext* context, const SetPropertyVec3Request* request, CommonReply* response);
	Status SetPropertyVec4(ServerContext* context, const SetPropertyVec4Request* request, CommonReply* response);
	Status SetPropertyColor(ServerContext* context, const SetPropertyColorRequest* request, CommonReply* response);
	Status SetPropertyDateTime(ServerContext* context, const SetPropertyDateTimeRequest* request, CommonReply* response);
	Status SetPropertyTimeSpan(ServerContext* context, const SetPropertyTimeSpanRequest* request, CommonReply* response);
	Status SetPropertyThickness(ServerContext* context, const SetPropertyThicknessRequest* request, CommonReply* response);
	Status SetPropertyEnum(ServerContext* context, const SetPropertyEnumRequest* request, CommonReply* response);
	Status SetPropertySolidColorBrush(ServerContext* context, const SetPropertySolidColorBrushRequest* request, CommonReply* response);
	Status SetPropertyImageBrush(ServerContext* context, const SetPropertyImageBrushRequest* request, CommonReply* response);
	Status SetPropertyLinearGradientBrush(ServerContext* context, const SetPropertyLinearGradientBrushRequest* request, CommonReply* response);

	std::pair<bool, std::string> _setProperty(const std::string &path, uint64 propertyID, const Poco::Dynamic::Var &v);
};