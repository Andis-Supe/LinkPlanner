#ifndef ELECTRICAL_SIGNAL_GENERATOR_H
#define ELECTRICAL_SIGNAL_GENERATOR_H

#include "netxpto.h"

using namespace std;
 
enum ElectricalSignalFunction{ContinuousWave};

class ElectricalSignalGenerator : public Block {

	/*Input Parameters*/
	ElectricalSignalFunction signalFunction{ ContinuousWave };
	double samplingPeriod{ 0.0 };
	double symbolPeriod{ 0.0 };
	double gainValue{ 1.0 };
	long int numberOfSamples{ -1.0 };

public:
	ElectricalSignalGenerator() {};
	ElectricalSignalGenerator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);

	bool runBlock(void);

	void setFunction(ElectricalSignalFunction fun) { signalFunction = fun; };
	ElectricalSignalFunction getFunction() { return signalFunction; };

	void setSamplingPeriod(double speriod) { samplingPeriod = speriod; };
	double getSamplingPeriod() { return samplingPeriod; };

	void setSymbolPeriod(double speriod) { symbolPeriod = speriod; };
	double getSymbolPeriod() { return symbolPeriod; };

	void setGain(double gvalue) { gainValue = gvalue; };
	double getGain() { return gainValue; };

	void setNumberOfSamples(long int nSample) { numberOfSamples = nSample; };
	long int getNumberOfSamples() { return numberOfSamples; };

};

#endif
