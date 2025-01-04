#include "novaservice.h"

#include <logger/logger.h>

#include "serviceAPI.h"

NovaService::NovaService() : requestsChannel("api", ipc::sender | ipc::receiver) {}

void NovaService::Process() {
	auto request = requestsChannel.recv(ipc::default_timeout);

	if (!request.empty()) {
		auto* requestBuffer = request.get<Request*>();

		LogInfo("Received request");

		if (requestBuffer->header == API_HEADER::GET_CREDITS) {
			LogInfo("Received request header is API_HEADER::GET_CREDITS");

			CreditsResponse res{ .value = 500 };
			res.header = API_HEADER::GET_CREDITS;
			ipc::buff_t resBuffer(&res, sizeof(CreditsResponse));
			requestsChannel.send(resBuffer);
		}
	}
}