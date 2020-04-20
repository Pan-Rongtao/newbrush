#pragma once
#include "Resources.grpc.pb.h"
#include "StubBase.h"

using namespace nbrpc;

class ResourceDictionaryStub : public ResourceDictionaryRpc::Service, public StubBase
{
	virtual Status AddBool(ServerContext* context, const AddBoolRequest* request, CommonReply* response);
	virtual Status AddInt(ServerContext* context, const AddIntRequest* request, CommonReply* response);
	virtual Status AddFloat(ServerContext* context, const AddFloatRequest* request, CommonReply* response);
	virtual Status AddString(ServerContext* context, const AddStringRequest* request, CommonReply* response);
	virtual Status AddSolidSolorBrush(ServerContext* context, const AddSolidSolorBrushRequest* request, CommonReply* response);
	virtual Status AddImageBrush(ServerContext* context, const AddImageBrushRequest* request, CommonReply* response);
};