#pragma once

#include "PyNet.DI/Module.h"
#include "InputLayer.h"
#include "DenseLayer.h"
#include "ConvolutionalLayer.h"
#include "MaxPoolingLayer.h"
#include "FlattenLayer.h"
#include "SoftmaxLayer.h"

using namespace PyNet::DI;

namespace PyNet::Infrastructure::Layers {

	class LayerModule : public Module {

	public:

		void Load(const ContextBuilder& builder) const override {

			builder.RegisterType<InputLayer>()
				->AsSelf();

			builder.RegisterType<DenseLayer>()
				->AsSelf();

			builder.RegisterType<ConvolutionalLayer>()
				->AsSelf();

			builder.RegisterType<MaxPoolingLayer>()
				->AsSelf();

			builder.RegisterType<FlattenLayer>()
				->AsSelf();

			builder.RegisterType<SoftmaxLayer>()
				->AsSelf();
		}
	};
}
