#pragma once

#include "PyNet.Models/Matrix.h"
#include "PyNet.DI/Context.h"
#include "PyNet.Models/ILogger.h"
#include "TrainableLayer.h"
#include <numeric>
#include <memory>

using namespace std;
using namespace PyNet::DI;

namespace PyNet::Infrastructure::Layers {

	class DenseLayer : public TrainableLayer {
	private:
		unique_ptr<Matrix> _weights;
		unique_ptr<Matrix> _dLoss_dWeightSum;
		double _bias = 0.01;
		double _dLoss_dBiasSum;
		shared_ptr<AdjustmentCalculator> _adjustmentCalculator;

		DenseLayer(shared_ptr<Context> context, shared_ptr<AdjustmentCalculator> adjustmentCalculator)  {
			_weights = context->GetUnique<Matrix>();
			_dLoss_dWeightSum = context->GetUnique<Matrix>();
			_adjustmentCalculator = adjustmentCalculator;
			Input = context->GetUnique<Matrix>();
		}

		unique_ptr<Matrix> dLoss_dWeight(const Matrix& inputLayer, const Matrix& dLoss_dOutput) const {
			return dLoss_dOutput * *~inputLayer;
		}

		double dLoss_dBias(const Matrix& dLoss_dOutput) const {

			return accumulate(dLoss_dOutput.begin(), dLoss_dOutput.end(), 0.0);
		}

	public:

		static auto factory(shared_ptr<Context> context, shared_ptr<AdjustmentCalculator> adjustmentCalculator) {
			return new DenseLayer(context, adjustmentCalculator);
		}

		void Initialise(size_t rows, size_t cols) {
			_weights->Initialise(rows, cols, true);
			_dLoss_dBiasSum = 0;
			_dLoss_dWeightSum->Initialise(rows, cols, false);
			Input->Initialise(cols, 1, false);
		}

		shared_ptr<Matrix> Apply(shared_ptr<Matrix> input) override {

			Input = input;
			Output = *_weights * *Input;

			*Output = *(* Output + _bias);

			return Output;
		}

		unique_ptr<Matrix> dLoss_dInput(const Matrix& dLoss_dOutput) const override {
			return *~*_weights * dLoss_dOutput;
		}

		void UpdateAdjustments(const Matrix& dLoss_dOutput) override {

			_dLoss_dBiasSum = _adjustmentCalculator->CalculateBiasAdjustment(dLoss_dBias(dLoss_dOutput), _dLoss_dBiasSum);
			_adjustmentCalculator->CalculateWeightAdjustment(*dLoss_dWeight(*Input, dLoss_dOutput), *_dLoss_dWeightSum);
		}

		Matrix& GetdLoss_dWeightSum() const override {
			return *_dLoss_dWeightSum;
		}

		double GetdLoss_dBiasSum() const override {
			return _dLoss_dBiasSum;
		}

		Matrix& GetWeights() override {
			return *_weights;
		}

		double& GetBias() override {
			return _bias;
		}
	};
}