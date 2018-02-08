# ifndef PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_
# define PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_


# include "netxpto_20180118.h"

# include <complex>
# include <random>
# include <vector>

class LocalOscillator : public Block {

	/* State Variables */


	/* Input Parameters */

	double opticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	double phase0{ 0 };
	double samplingPeriod{ 0.0 };
	double symbolPeriod{ 0.0 };
	double laserLW{ 0.0 };
	double laserRIN{ 0.0 };

	default_random_engine generatorRIN;
	default_random_engine generatorPhaseNoise;
	double signaltoNoiseRatio{ 0 };

public:

	/* Methods */
	LocalOscillator() {};
	LocalOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }
	void setSymbolPeriod(double sPeriod) { symbolPeriod = sPeriod; }
	void setOpticalPower(double oPower) { opticalPower = oPower; }
	void setOpticalPower_dBm(double oPower_dBm) { opticalPower = 1e-3*pow(10, oPower_dBm / 10); }

	void setWavelength(double wlength) { outputOpticalWavelength = wlength;  outputOpticalFrequency = SPEED_OF_LIGHT / outputOpticalWavelength; }
	double getWavelength() { return outputOpticalWavelength; }

	void setFrequency(double freq) { outputOpticalFrequency = freq;  outputOpticalWavelength = SPEED_OF_LIGHT / outputOpticalFrequency; }
	double getFrequency() { return outputOpticalFrequency; }
	
	void setPhase(double lOscillatorPhase) { phase0 = lOscillatorPhase; }
	double const getPhase(void) { return phase0; }

    void setSignaltoNoiseRatio(double sNoiseRatio) { signaltoNoiseRatio=sNoiseRatio; }
	double const getSignaltoNoiseRatio(void){ return signaltoNoiseRatio; }
	
	void setLaserLinewidth(double laserLinewidth) { laserLW = laserLinewidth; }
	double getLaserLinewidth() { return laserLW; }

	void setLaserRIN(double lRIN) { laserRIN = lRIN; }
	double getLaserRIN() { return laserRIN; }
};

#endif 
