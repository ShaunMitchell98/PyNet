#pragma once
#include "Activations/Activation.h"
#include "Headers.h"
#include "Settings.h"

using namespace PyNet::Models;
using namespace PyNet::Infrastructure::Activations;

namespace PyNet::Infrastructure {
	extern "C" {

		EXPORT void* PyNetwork_Initialise(LogLevel logLevel, bool cudaEnabled);

		EXPORT void PyNetwork_Destruct(void* input);

		EXPORT void PyNetwork_AddInputLayer(void* input, int rows, int cols, double dropoutRate);

		EXPORT void PyNetwork_AddDenseLayer(void* input, int count, ActivationFunctionType activationFunctionType, double dropoutRate);

		EXPORT void PyNetwork_AddConvolutionLayer(void* input, int filterSize, ActivationFunctionType activationFunctionType);

		EXPORT void PyNetwork_AddMaxPoolingLayer(void* input, int filterSize);

		EXPORT void PyNetwork_AddFlattenLayer(void* input);

		//EXPORT void PyNetwork_AddSoftmaxLayer(void* input);

		EXPORT const double* PyNetwork_Run(void* input, double* inputLayer);

		EXPORT void PyNetwork_SetVariableLearning(void* input, double errorThreshold, double lrDecrease, double lrIncrease);

		EXPORT void PyNetwork_Train(void* input, double** inputLayers, double** expectedOutputs, Settings* settings);
	}
}