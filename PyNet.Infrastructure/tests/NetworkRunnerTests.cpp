#include "UnitTest.h"
#include "PyNet.Models.Cpu/CpuMatrix.h"
#include "../Src/Layers/InputLayer.h"
#include "Layers/FakeLayer.h"
#include "../Src/NetworkRunner.h"

using namespace PyNet::Models::Cpu;
using namespace PyNet::DI;
using namespace PyNet::Infrastructure::Layers;

namespace PyNet::Infrastructure::Tests
{
	class NetworkRunnerTests : public UnitTest {};

	TEST_F(NetworkRunnerTests, NetworkRunner_GivenInput_ReturnsOutput) 
	{
		auto pyNetwork = GetSharedService<PyNetwork>();

		double inputValues[5] = { 1.2, 2.4, 3.9, 4.3, 5.2 };

		auto input = GetSharedService<Matrix>();
		input->Initialise(5, 1);
		*input = inputValues;

		auto inputLayer = GetUniqueService<InputLayer>();
		inputLayer->Initialise(5, 1);

		pyNetwork->Layers.push_back(move(inputLayer));

		auto fakeLayer = GetUniqueService<FakeLayer>();

		auto fakeValue = 0.2;

		fakeLayer->SetValue(fakeValue);

		pyNetwork->Layers.push_back(move(fakeLayer));

		auto networkRunner = GetUniqueService<NetworkRunner>();

		auto result = networkRunner->Run(input);

		for (auto& value : *result)
		{
			ASSERT_FLOAT_EQ(fakeValue, value);
		}
	}
}