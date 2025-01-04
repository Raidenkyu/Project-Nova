#include <iostream>

#include "libipc/ipc.h"

#include "../service/serviceAPI.h"

int main() {
	ipc::channel requestsChannel("api", ipc::sender | ipc::receiver);

	Request req{ .header = API_HEADER::GET_CREDITS };
	ipc::buff_t buff(&req, sizeof(Request));

	if (!requestsChannel.send(buff)) {
		std::cout << "Failed to send!\n";
	}

	ipc::buff_t resBuff = requestsChannel.recv(1000);
	auto* res = resBuff.get<Response*>();

	if (res->header == API_HEADER::GET_CREDITS) {
		auto* creditsResponse = reinterpret_cast<CreditsResponse*>(res);

		std::cout << "Current Credits: " << creditsResponse->value << std::endl;
	} else {
		std::cout << "Response with Unknown header\n";
	}

	return 0;
}