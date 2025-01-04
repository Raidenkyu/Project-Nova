#pragma once

#include "libipc/ipc.h"

class NovaService {
public:
	NovaService();

	void Process();
private:
	ipc::channel requestsChannel;
};
