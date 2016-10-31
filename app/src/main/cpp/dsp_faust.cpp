//----------------------------------------------------------
//
// Code generated with Faust 0.9.92 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
/************************************************************************
 ************************************************************************
 FAUST Architecture File for Android
 Copyright (C) 2016 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------

 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include <math.h>
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif

/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif

//**************************************************************
// DSP class
//**************************************************************


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	float 	fConst2;
	FAUSTFLOAT 	fslider2;
	float 	fVec0[2];
	int 	iVec1[2];
	float 	fRec3[2];
	float 	fConst3;
	float 	fConst4;
	int 	iRec4[2];
	float 	fRec2[3];
	FAUSTFLOAT 	fslider3;
	float 	fVec2[2];
	int 	iVec3[2];
	float 	fRec6[2];
	float 	fRec5[3];
	FAUSTFLOAT 	fslider4;
	float 	fVec4[2];
	int 	iVec5[2];
	float 	fRec8[2];
	float 	fRec7[3];
	FAUSTFLOAT 	fslider5;
	float 	fVec6[2];
	int 	iVec7[2];
	float 	fRec10[2];
	float 	fRec9[3];
	FAUSTFLOAT 	fslider6;
	float 	fVec8[2];
	int 	iVec9[2];
	float 	fRec12[2];
	float 	fRec11[3];
	FAUSTFLOAT 	fslider7;
	float 	fVec10[2];
	int 	iVec11[2];
	float 	fRec14[2];
	float 	fRec13[3];
	FAUSTFLOAT 	fslider8;
	float 	fVec12[2];
	int 	iVec13[2];
	float 	fRec16[2];
	float 	fRec15[3];
	FAUSTFLOAT 	fslider9;
	float 	fVec14[2];
	int 	iVec15[2];
	float 	fRec18[2];
	float 	fRec17[3];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	float 	fConst5;
	float 	fRec19[3];
	float 	fRec20[3];
	float 	fRec21[3];
	float 	fRec22[3];
	float 	fRec23[3];
	float 	fRec24[3];
	float 	fRec25[3];
	float 	fRec26[3];
	float 	fConst6;
	float 	fRec27[3];
	float 	fRec28[3];
	float 	fRec29[3];
	float 	fRec30[3];
	float 	fRec31[3];
	float 	fRec32[3];
	float 	fRec33[3];
	float 	fRec34[3];
	float 	fConst7;
	float 	fRec35[3];
	float 	fRec36[3];
	float 	fRec37[3];
	float 	fRec38[3];
	float 	fRec39[3];
	float 	fRec40[3];
	float 	fRec41[3];
	float 	fRec42[3];
	float 	fConst8;
	float 	fRec43[3];
	float 	fRec44[3];
	float 	fRec45[3];
	float 	fRec46[3];
	float 	fRec47[3];
	float 	fRec48[3];
	float 	fRec49[3];
	float 	fRec50[3];
	float 	fConst9;
	float 	fRec51[3];
	float 	fRec52[3];
	float 	fRec53[3];
	float 	fRec54[3];
	float 	fRec55[3];
	float 	fRec56[3];
	float 	fRec57[3];
	float 	fRec58[3];
	float 	fConst10;
	float 	fRec59[3];
	float 	fRec60[3];
	float 	fRec61[3];
	float 	fRec62[3];
	float 	fRec63[3];
	float 	fRec64[3];
	float 	fRec65[3];
	float 	fRec66[3];
	float 	fConst11;
	float 	fRec67[3];
	float 	fRec68[3];
	float 	fRec69[3];
	float 	fRec70[3];
	float 	fRec71[3];
	float 	fRec72[3];
	float 	fRec73[3];
	float 	fRec74[3];
	float 	fConst12;
	float 	fRec75[3];
	float 	fRec76[3];
	float 	fRec77[3];
	float 	fRec78[3];
	float 	fRec79[3];
	float 	fRec80[3];
	float 	fRec81[3];
	float 	fRec82[3];
	float 	fConst13;
	float 	fRec83[3];
	float 	fRec84[3];
	float 	fRec85[3];
	float 	fRec86[3];
	float 	fRec87[3];
	float 	fRec88[3];
	float 	fRec89[3];
	float 	fRec90[3];
	float 	fConst14;
	float 	fRec91[3];
	float 	fRec92[3];
	float 	fRec93[3];
	float 	fRec94[3];
	float 	fRec95[3];
	float 	fRec96[3];
	float 	fRec97[3];
	float 	fRec98[3];
	float 	fConst15;
	float 	fRec99[3];
	float 	fRec100[3];
	float 	fRec101[3];
	float 	fRec102[3];
	float 	fRec103[3];
	float 	fRec104[3];
	float 	fRec105[3];
	float 	fRec106[3];
	float 	fConst16;
	float 	fRec107[3];
	float 	fRec108[3];
	float 	fRec109[3];
	float 	fRec110[3];
	float 	fRec111[3];
	float 	fRec112[3];
	float 	fRec113[3];
	float 	fRec114[3];
	float 	fConst17;
	float 	fRec115[3];
	float 	fRec116[3];
	float 	fRec117[3];
	float 	fRec118[3];
	float 	fRec119[3];
	float 	fRec120[3];
	float 	fRec121[3];
	float 	fRec122[3];
	float 	fConst18;
	float 	fRec123[3];
	float 	fRec124[3];
	float 	fRec125[3];
	float 	fRec126[3];
	float 	fRec127[3];
	float 	fRec128[3];
	float 	fRec129[3];
	float 	fRec130[3];
	float 	fConst19;
	float 	fRec131[3];
	float 	fRec132[3];
	float 	fRec133[3];
	float 	fRec134[3];
	float 	fRec135[3];
	float 	fRec136[3];
	float 	fRec137[3];
	float 	fRec138[3];
	float 	fConst20;
	float 	fRec139[3];
	float 	fRec140[3];
	float 	fRec141[3];
	float 	fRec142[3];
	float 	fRec143[3];
	float 	fRec144[3];
	float 	fRec145[3];
	float 	fRec146[3];
	float 	fConst21;
	float 	fRec147[3];
	float 	fRec148[3];
	float 	fRec149[3];
	float 	fRec150[3];
	float 	fRec151[3];
	float 	fRec152[3];
	float 	fRec153[3];
	float 	fRec154[3];
	float 	fConst22;
	float 	fRec155[3];
	float 	fRec156[3];
	float 	fRec157[3];
	float 	fRec158[3];
	float 	fRec159[3];
	float 	fRec160[3];
	float 	fRec161[3];
	float 	fRec162[3];
	float 	fConst23;
	float 	fRec163[3];
	float 	fRec164[3];
	float 	fRec165[3];
	float 	fRec166[3];
	float 	fRec167[3];
	float 	fRec168[3];
	float 	fRec169[3];
	float 	fRec170[3];
	float 	fConst24;
	float 	fRec171[3];
	float 	fRec172[3];
	float 	fRec173[3];
	float 	fRec174[3];
	float 	fRec175[3];
	float 	fRec176[3];
	float 	fRec177[3];
	float 	fRec178[3];
	float 	fConst25;
	float 	fRec179[3];
	float 	fRec180[3];
	float 	fRec181[3];
	float 	fRec182[3];
	float 	fRec183[3];
	float 	fRec184[3];
	float 	fRec185[3];
	float 	fRec186[3];
	float 	fConst26;
	float 	fRec187[3];
	float 	fRec188[3];
	float 	fRec189[3];
	float 	fRec190[3];
	float 	fRec191[3];
	float 	fRec192[3];
	float 	fRec193[3];
	float 	fRec194[3];
	float 	fConst27;
	float 	fRec195[3];
	float 	fRec196[3];
	float 	fRec197[3];
	float 	fRec198[3];
	float 	fRec199[3];
	float 	fRec200[3];
	float 	fRec201[3];
	float 	fRec202[3];
	float 	fConst28;
	float 	fRec203[3];
	float 	fRec204[3];
	float 	fRec205[3];
	float 	fRec206[3];
	float 	fRec207[3];
	float 	fRec208[3];
	float 	fRec209[3];
	float 	fRec210[3];
	float 	fConst29;
	float 	fRec211[3];
	float 	fRec212[3];
	float 	fRec213[3];
	float 	fRec214[3];
	float 	fRec215[3];
	float 	fRec216[3];
	float 	fRec217[3];
	float 	fRec218[3];
	float 	fConst30;
	float 	fRec219[3];
	float 	fRec220[3];
	float 	fRec221[3];
	float 	fRec222[3];
	float 	fRec223[3];
	float 	fRec224[3];
	float 	fRec225[3];
	float 	fRec226[3];
	float 	fConst31;
	float 	fRec227[3];
	float 	fRec228[3];
	float 	fRec229[3];
	float 	fRec230[3];
	float 	fRec231[3];
	float 	fRec232[3];
	float 	fRec233[3];
	float 	fRec234[3];
	float 	fConst32;
	float 	fRec235[3];
	float 	fRec236[3];
	float 	fRec237[3];
	float 	fRec238[3];
	float 	fRec239[3];
	float 	fRec240[3];
	float 	fRec241[3];
	float 	fRec242[3];
	float 	fConst33;
	float 	fRec243[3];
	float 	fRec244[3];
	float 	fRec245[3];
	float 	fRec246[3];
	float 	fRec247[3];
	float 	fRec248[3];
	float 	fRec249[3];
	float 	fRec250[3];
	int 	iConst34;
	int 	IOTA;
	float 	fRec1[32768];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	float 	fRec0[131072];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("envelope.lib/name", "Faust Envelope Library");
		m->declare("envelope.lib/version", "0.0");
		m->declare("envelope.lib/author", "GRAME");
		m->declare("envelope.lib/copyright", "GRAME");
		m->declare("envelope.lib/license", "LGPL with exception");
		m->declare("noise.lib/name", "Faust Noise Generator Library");
		m->declare("noise.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831855f / fConst0);
		fConst2 = (0.002f * fConst0);
		fConst3 = (0.001f * fConst0);
		fConst4 = (1e+03f / fConst0);
		fConst5 = (0.9032963f * fConst0);
		fConst6 = (0.81303704f * fConst0);
		fConst7 = (0.729f * fConst0);
		fConst8 = (0.65096295f * fConst0);
		fConst9 = (0.5787037f * fConst0);
		fConst10 = (0.512f * fConst0);
		fConst11 = (0.45062962f * fConst0);
		fConst12 = (0.39437038f * fConst0);
		fConst13 = (0.343f * fConst0);
		fConst14 = (0.2962963f * fConst0);
		fConst15 = (0.25403702f * fConst0);
		fConst16 = (0.216f * fConst0);
		fConst17 = (0.18196297f * fConst0);
		fConst18 = (0.1517037f * fConst0);
		fConst19 = (0.125f * fConst0);
		fConst20 = (0.10162963f * fConst0);
		fConst21 = (0.08137037f * fConst0);
		fConst22 = (0.064f * fConst0);
		fConst23 = (0.049296297f * fConst0);
		fConst24 = (0.037037037f * fConst0);
		fConst25 = (0.027f * fConst0);
		fConst26 = (0.018962963f * fConst0);
		fConst27 = (0.012703704f * fConst0);
		fConst28 = (0.008f * fConst0);
		fConst29 = (0.0046296297f * fConst0);
		fConst30 = (0.0023703703f * fConst0);
		fConst31 = (0.001f * fConst0);
		fConst32 = (0.0002962963f * fConst0);
		fConst33 = (3.7037036e-05f * fConst0);
		iConst34 = int((int((int((0.07f * fConst0)) & 65535)) + 1));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 2.5f;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 0.0f;
		fslider8 = 0.0f;
		fslider9 = 0.0f;
		fslider10 = 0.5f;
		fslider11 = 0.5f;
		fslider12 = 1.0f;
		fslider13 = 0.1f;
		fslider14 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) iVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) iRec4[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) iVec3[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) iVec5[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) iVec7[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) iVec9[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) iVec11[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<3; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) iVec13[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<3; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) iVec15[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<3; i++) fRec17[i] = 0;
		for (int i=0; i<3; i++) fRec19[i] = 0;
		for (int i=0; i<3; i++) fRec20[i] = 0;
		for (int i=0; i<3; i++) fRec21[i] = 0;
		for (int i=0; i<3; i++) fRec22[i] = 0;
		for (int i=0; i<3; i++) fRec23[i] = 0;
		for (int i=0; i<3; i++) fRec24[i] = 0;
		for (int i=0; i<3; i++) fRec25[i] = 0;
		for (int i=0; i<3; i++) fRec26[i] = 0;
		for (int i=0; i<3; i++) fRec27[i] = 0;
		for (int i=0; i<3; i++) fRec28[i] = 0;
		for (int i=0; i<3; i++) fRec29[i] = 0;
		for (int i=0; i<3; i++) fRec30[i] = 0;
		for (int i=0; i<3; i++) fRec31[i] = 0;
		for (int i=0; i<3; i++) fRec32[i] = 0;
		for (int i=0; i<3; i++) fRec33[i] = 0;
		for (int i=0; i<3; i++) fRec34[i] = 0;
		for (int i=0; i<3; i++) fRec35[i] = 0;
		for (int i=0; i<3; i++) fRec36[i] = 0;
		for (int i=0; i<3; i++) fRec37[i] = 0;
		for (int i=0; i<3; i++) fRec38[i] = 0;
		for (int i=0; i<3; i++) fRec39[i] = 0;
		for (int i=0; i<3; i++) fRec40[i] = 0;
		for (int i=0; i<3; i++) fRec41[i] = 0;
		for (int i=0; i<3; i++) fRec42[i] = 0;
		for (int i=0; i<3; i++) fRec43[i] = 0;
		for (int i=0; i<3; i++) fRec44[i] = 0;
		for (int i=0; i<3; i++) fRec45[i] = 0;
		for (int i=0; i<3; i++) fRec46[i] = 0;
		for (int i=0; i<3; i++) fRec47[i] = 0;
		for (int i=0; i<3; i++) fRec48[i] = 0;
		for (int i=0; i<3; i++) fRec49[i] = 0;
		for (int i=0; i<3; i++) fRec50[i] = 0;
		for (int i=0; i<3; i++) fRec51[i] = 0;
		for (int i=0; i<3; i++) fRec52[i] = 0;
		for (int i=0; i<3; i++) fRec53[i] = 0;
		for (int i=0; i<3; i++) fRec54[i] = 0;
		for (int i=0; i<3; i++) fRec55[i] = 0;
		for (int i=0; i<3; i++) fRec56[i] = 0;
		for (int i=0; i<3; i++) fRec57[i] = 0;
		for (int i=0; i<3; i++) fRec58[i] = 0;
		for (int i=0; i<3; i++) fRec59[i] = 0;
		for (int i=0; i<3; i++) fRec60[i] = 0;
		for (int i=0; i<3; i++) fRec61[i] = 0;
		for (int i=0; i<3; i++) fRec62[i] = 0;
		for (int i=0; i<3; i++) fRec63[i] = 0;
		for (int i=0; i<3; i++) fRec64[i] = 0;
		for (int i=0; i<3; i++) fRec65[i] = 0;
		for (int i=0; i<3; i++) fRec66[i] = 0;
		for (int i=0; i<3; i++) fRec67[i] = 0;
		for (int i=0; i<3; i++) fRec68[i] = 0;
		for (int i=0; i<3; i++) fRec69[i] = 0;
		for (int i=0; i<3; i++) fRec70[i] = 0;
		for (int i=0; i<3; i++) fRec71[i] = 0;
		for (int i=0; i<3; i++) fRec72[i] = 0;
		for (int i=0; i<3; i++) fRec73[i] = 0;
		for (int i=0; i<3; i++) fRec74[i] = 0;
		for (int i=0; i<3; i++) fRec75[i] = 0;
		for (int i=0; i<3; i++) fRec76[i] = 0;
		for (int i=0; i<3; i++) fRec77[i] = 0;
		for (int i=0; i<3; i++) fRec78[i] = 0;
		for (int i=0; i<3; i++) fRec79[i] = 0;
		for (int i=0; i<3; i++) fRec80[i] = 0;
		for (int i=0; i<3; i++) fRec81[i] = 0;
		for (int i=0; i<3; i++) fRec82[i] = 0;
		for (int i=0; i<3; i++) fRec83[i] = 0;
		for (int i=0; i<3; i++) fRec84[i] = 0;
		for (int i=0; i<3; i++) fRec85[i] = 0;
		for (int i=0; i<3; i++) fRec86[i] = 0;
		for (int i=0; i<3; i++) fRec87[i] = 0;
		for (int i=0; i<3; i++) fRec88[i] = 0;
		for (int i=0; i<3; i++) fRec89[i] = 0;
		for (int i=0; i<3; i++) fRec90[i] = 0;
		for (int i=0; i<3; i++) fRec91[i] = 0;
		for (int i=0; i<3; i++) fRec92[i] = 0;
		for (int i=0; i<3; i++) fRec93[i] = 0;
		for (int i=0; i<3; i++) fRec94[i] = 0;
		for (int i=0; i<3; i++) fRec95[i] = 0;
		for (int i=0; i<3; i++) fRec96[i] = 0;
		for (int i=0; i<3; i++) fRec97[i] = 0;
		for (int i=0; i<3; i++) fRec98[i] = 0;
		for (int i=0; i<3; i++) fRec99[i] = 0;
		for (int i=0; i<3; i++) fRec100[i] = 0;
		for (int i=0; i<3; i++) fRec101[i] = 0;
		for (int i=0; i<3; i++) fRec102[i] = 0;
		for (int i=0; i<3; i++) fRec103[i] = 0;
		for (int i=0; i<3; i++) fRec104[i] = 0;
		for (int i=0; i<3; i++) fRec105[i] = 0;
		for (int i=0; i<3; i++) fRec106[i] = 0;
		for (int i=0; i<3; i++) fRec107[i] = 0;
		for (int i=0; i<3; i++) fRec108[i] = 0;
		for (int i=0; i<3; i++) fRec109[i] = 0;
		for (int i=0; i<3; i++) fRec110[i] = 0;
		for (int i=0; i<3; i++) fRec111[i] = 0;
		for (int i=0; i<3; i++) fRec112[i] = 0;
		for (int i=0; i<3; i++) fRec113[i] = 0;
		for (int i=0; i<3; i++) fRec114[i] = 0;
		for (int i=0; i<3; i++) fRec115[i] = 0;
		for (int i=0; i<3; i++) fRec116[i] = 0;
		for (int i=0; i<3; i++) fRec117[i] = 0;
		for (int i=0; i<3; i++) fRec118[i] = 0;
		for (int i=0; i<3; i++) fRec119[i] = 0;
		for (int i=0; i<3; i++) fRec120[i] = 0;
		for (int i=0; i<3; i++) fRec121[i] = 0;
		for (int i=0; i<3; i++) fRec122[i] = 0;
		for (int i=0; i<3; i++) fRec123[i] = 0;
		for (int i=0; i<3; i++) fRec124[i] = 0;
		for (int i=0; i<3; i++) fRec125[i] = 0;
		for (int i=0; i<3; i++) fRec126[i] = 0;
		for (int i=0; i<3; i++) fRec127[i] = 0;
		for (int i=0; i<3; i++) fRec128[i] = 0;
		for (int i=0; i<3; i++) fRec129[i] = 0;
		for (int i=0; i<3; i++) fRec130[i] = 0;
		for (int i=0; i<3; i++) fRec131[i] = 0;
		for (int i=0; i<3; i++) fRec132[i] = 0;
		for (int i=0; i<3; i++) fRec133[i] = 0;
		for (int i=0; i<3; i++) fRec134[i] = 0;
		for (int i=0; i<3; i++) fRec135[i] = 0;
		for (int i=0; i<3; i++) fRec136[i] = 0;
		for (int i=0; i<3; i++) fRec137[i] = 0;
		for (int i=0; i<3; i++) fRec138[i] = 0;
		for (int i=0; i<3; i++) fRec139[i] = 0;
		for (int i=0; i<3; i++) fRec140[i] = 0;
		for (int i=0; i<3; i++) fRec141[i] = 0;
		for (int i=0; i<3; i++) fRec142[i] = 0;
		for (int i=0; i<3; i++) fRec143[i] = 0;
		for (int i=0; i<3; i++) fRec144[i] = 0;
		for (int i=0; i<3; i++) fRec145[i] = 0;
		for (int i=0; i<3; i++) fRec146[i] = 0;
		for (int i=0; i<3; i++) fRec147[i] = 0;
		for (int i=0; i<3; i++) fRec148[i] = 0;
		for (int i=0; i<3; i++) fRec149[i] = 0;
		for (int i=0; i<3; i++) fRec150[i] = 0;
		for (int i=0; i<3; i++) fRec151[i] = 0;
		for (int i=0; i<3; i++) fRec152[i] = 0;
		for (int i=0; i<3; i++) fRec153[i] = 0;
		for (int i=0; i<3; i++) fRec154[i] = 0;
		for (int i=0; i<3; i++) fRec155[i] = 0;
		for (int i=0; i<3; i++) fRec156[i] = 0;
		for (int i=0; i<3; i++) fRec157[i] = 0;
		for (int i=0; i<3; i++) fRec158[i] = 0;
		for (int i=0; i<3; i++) fRec159[i] = 0;
		for (int i=0; i<3; i++) fRec160[i] = 0;
		for (int i=0; i<3; i++) fRec161[i] = 0;
		for (int i=0; i<3; i++) fRec162[i] = 0;
		for (int i=0; i<3; i++) fRec163[i] = 0;
		for (int i=0; i<3; i++) fRec164[i] = 0;
		for (int i=0; i<3; i++) fRec165[i] = 0;
		for (int i=0; i<3; i++) fRec166[i] = 0;
		for (int i=0; i<3; i++) fRec167[i] = 0;
		for (int i=0; i<3; i++) fRec168[i] = 0;
		for (int i=0; i<3; i++) fRec169[i] = 0;
		for (int i=0; i<3; i++) fRec170[i] = 0;
		for (int i=0; i<3; i++) fRec171[i] = 0;
		for (int i=0; i<3; i++) fRec172[i] = 0;
		for (int i=0; i<3; i++) fRec173[i] = 0;
		for (int i=0; i<3; i++) fRec174[i] = 0;
		for (int i=0; i<3; i++) fRec175[i] = 0;
		for (int i=0; i<3; i++) fRec176[i] = 0;
		for (int i=0; i<3; i++) fRec177[i] = 0;
		for (int i=0; i<3; i++) fRec178[i] = 0;
		for (int i=0; i<3; i++) fRec179[i] = 0;
		for (int i=0; i<3; i++) fRec180[i] = 0;
		for (int i=0; i<3; i++) fRec181[i] = 0;
		for (int i=0; i<3; i++) fRec182[i] = 0;
		for (int i=0; i<3; i++) fRec183[i] = 0;
		for (int i=0; i<3; i++) fRec184[i] = 0;
		for (int i=0; i<3; i++) fRec185[i] = 0;
		for (int i=0; i<3; i++) fRec186[i] = 0;
		for (int i=0; i<3; i++) fRec187[i] = 0;
		for (int i=0; i<3; i++) fRec188[i] = 0;
		for (int i=0; i<3; i++) fRec189[i] = 0;
		for (int i=0; i<3; i++) fRec190[i] = 0;
		for (int i=0; i<3; i++) fRec191[i] = 0;
		for (int i=0; i<3; i++) fRec192[i] = 0;
		for (int i=0; i<3; i++) fRec193[i] = 0;
		for (int i=0; i<3; i++) fRec194[i] = 0;
		for (int i=0; i<3; i++) fRec195[i] = 0;
		for (int i=0; i<3; i++) fRec196[i] = 0;
		for (int i=0; i<3; i++) fRec197[i] = 0;
		for (int i=0; i<3; i++) fRec198[i] = 0;
		for (int i=0; i<3; i++) fRec199[i] = 0;
		for (int i=0; i<3; i++) fRec200[i] = 0;
		for (int i=0; i<3; i++) fRec201[i] = 0;
		for (int i=0; i<3; i++) fRec202[i] = 0;
		for (int i=0; i<3; i++) fRec203[i] = 0;
		for (int i=0; i<3; i++) fRec204[i] = 0;
		for (int i=0; i<3; i++) fRec205[i] = 0;
		for (int i=0; i<3; i++) fRec206[i] = 0;
		for (int i=0; i<3; i++) fRec207[i] = 0;
		for (int i=0; i<3; i++) fRec208[i] = 0;
		for (int i=0; i<3; i++) fRec209[i] = 0;
		for (int i=0; i<3; i++) fRec210[i] = 0;
		for (int i=0; i<3; i++) fRec211[i] = 0;
		for (int i=0; i<3; i++) fRec212[i] = 0;
		for (int i=0; i<3; i++) fRec213[i] = 0;
		for (int i=0; i<3; i++) fRec214[i] = 0;
		for (int i=0; i<3; i++) fRec215[i] = 0;
		for (int i=0; i<3; i++) fRec216[i] = 0;
		for (int i=0; i<3; i++) fRec217[i] = 0;
		for (int i=0; i<3; i++) fRec218[i] = 0;
		for (int i=0; i<3; i++) fRec219[i] = 0;
		for (int i=0; i<3; i++) fRec220[i] = 0;
		for (int i=0; i<3; i++) fRec221[i] = 0;
		for (int i=0; i<3; i++) fRec222[i] = 0;
		for (int i=0; i<3; i++) fRec223[i] = 0;
		for (int i=0; i<3; i++) fRec224[i] = 0;
		for (int i=0; i<3; i++) fRec225[i] = 0;
		for (int i=0; i<3; i++) fRec226[i] = 0;
		for (int i=0; i<3; i++) fRec227[i] = 0;
		for (int i=0; i<3; i++) fRec228[i] = 0;
		for (int i=0; i<3; i++) fRec229[i] = 0;
		for (int i=0; i<3; i++) fRec230[i] = 0;
		for (int i=0; i<3; i++) fRec231[i] = 0;
		for (int i=0; i<3; i++) fRec232[i] = 0;
		for (int i=0; i<3; i++) fRec233[i] = 0;
		for (int i=0; i<3; i++) fRec234[i] = 0;
		for (int i=0; i<3; i++) fRec235[i] = 0;
		for (int i=0; i<3; i++) fRec236[i] = 0;
		for (int i=0; i<3; i++) fRec237[i] = 0;
		for (int i=0; i<3; i++) fRec238[i] = 0;
		for (int i=0; i<3; i++) fRec239[i] = 0;
		for (int i=0; i<3; i++) fRec240[i] = 0;
		for (int i=0; i<3; i++) fRec241[i] = 0;
		for (int i=0; i<3; i++) fRec242[i] = 0;
		for (int i=0; i<3; i++) fRec243[i] = 0;
		for (int i=0; i<3; i++) fRec244[i] = 0;
		for (int i=0; i<3; i++) fRec245[i] = 0;
		for (int i=0; i<3; i++) fRec246[i] = 0;
		for (int i=0; i<3; i++) fRec247[i] = 0;
		for (int i=0; i<3; i++) fRec248[i] = 0;
		for (int i=0; i<3; i++) fRec249[i] = 0;
		for (int i=0; i<3; i++) fRec250[i] = 0;
		IOTA = 0;
		for (int i=0; i<32768; i++) fRec1[i] = 0;
		for (int i=0; i<131072; i++) fRec0[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fslider3, "midi", "ctrl 0");
		ui_interface->addHorizontalSlider("ctl0", &fslider3, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider2, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("ctl1", &fslider2, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider4, "midi", "ctrl 2");
		ui_interface->addHorizontalSlider("ctl2", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider5, "midi", "ctrl 3");
		ui_interface->addHorizontalSlider("ctl3", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider6, "midi", "ctrl 4");
		ui_interface->addHorizontalSlider("ctl4", &fslider6, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider7, "midi", "ctrl 5");
		ui_interface->addHorizontalSlider("ctl5", &fslider7, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider8, "midi", "ctrl 6");
		ui_interface->addHorizontalSlider("ctl6", &fslider8, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider9, "midi", "ctrl 7");
		ui_interface->addHorizontalSlider("ctl7", &fslider9, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("delLeg", &fslider13, 0.1f, 0.01f, 1.0f, 0.01f);
		ui_interface->declare(&fslider14, "acc", "1 0 0 0 10");
		ui_interface->addHorizontalSlider("feedback", &fslider14, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("gain", &fslider12, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("noteScale", &fslider0, 0.0f, 0.0f, 9.0f, 1.0f);
		ui_interface->declare(&fslider10, "acc", "0 0 -10 0 10");
		ui_interface->addHorizontalSlider("scale", &fslider10, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider11, "acc", "1 0 0 0 10");
		ui_interface->addHorizontalSlider("spread", &fslider11, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("t60", &fslider1, 2.5f, 0.01f, 5.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		int 	iSlow0 = int(float(fslider0));
		int 	iSlow1 = (iSlow0 == 5);
		int 	iSlow2 = (iSlow0 == 6);
		int 	iSlow3 = (iSlow0 == 4);
		int 	iSlow4 = (iSlow0 == 3);
		int 	iSlow5 = (iSlow4 + (iSlow3 + (iSlow2 + iSlow1)));
		int 	iSlow6 = (iSlow0 == 9);
		int 	iSlow7 = (iSlow0 == 7);
		int 	iSlow8 = (iSlow0 == 8);
		int 	iSlow9 = (iSlow8 + iSlow7);
		int 	iSlow10 = (iSlow0 == 2);
		int 	iSlow11 = (iSlow0 == 1);
		int 	iSlow12 = (iSlow0 == 0);
		float 	fSlow13 = ((293.66476f * (iSlow12 + (iSlow11 + (iSlow10 + iSlow9)))) + ((277.18262f * iSlow6) + (261.62558f * iSlow5)));
		float 	fSlow14 = float(fslider1);
		float 	fSlow15 = powf(0.001f,(1.0f / float((fConst0 * fSlow14))));
		float 	fSlow16 = (0 - (2 * fSlow15));
		float 	fSlow17 = (fSlow16 * cosf((fConst1 * fSlow13)));
		float 	fSlow18 = faustpower<2>(fSlow15);
		float 	fSlow19 = float(fslider2);
		float 	fSlow20 = (4.656613e-10f * faustpower<2>(fSlow19));
		int 	iSlow21 = (iSlow6 + iSlow8);
		int 	iSlow22 = (iSlow7 + iSlow21);
		float 	fSlow23 = ((195.99771f * iSlow5) + (261.62558f * (iSlow12 + (iSlow11 + (iSlow10 + iSlow22)))));
		float 	fSlow24 = (fSlow16 * cosf((fConst1 * fSlow23)));
		float 	fSlow25 = float(fslider3);
		float 	fSlow26 = (4.656613e-10f * faustpower<2>(fSlow25));
		float 	fSlow27 = ((311.12698f * (iSlow11 + (iSlow1 + (iSlow2 + iSlow9)))) + ((293.66476f * (iSlow3 + iSlow4)) + (329.62756f * (iSlow12 + (iSlow6 + iSlow10)))));
		float 	fSlow28 = (fSlow16 * cosf((fConst1 * fSlow27)));
		float 	fSlow29 = float(fslider4);
		float 	fSlow30 = (4.656613e-10f * faustpower<2>(fSlow29));
		float 	fSlow31 = (((369.99442f * (iSlow8 + iSlow10)) + ((311.12698f * iSlow3) + (329.62756f * (iSlow2 + iSlow4)))) + (349.22824f * (iSlow12 + (iSlow11 + (iSlow1 + (iSlow6 + iSlow7))))));
		float 	fSlow32 = (fSlow16 * cosf((fConst1 * fSlow31)));
		float 	fSlow33 = float(fslider5);
		float 	fSlow34 = (4.656613e-10f * faustpower<2>(fSlow33));
		float 	fSlow35 = (((415.3047f * iSlow10) + ((329.62756f * iSlow3) + ((349.22824f * iSlow2) + (369.99442f * iSlow7)))) + (391.99542f * (iSlow12 + (iSlow11 + (iSlow4 + (iSlow1 + iSlow21))))));
		float 	fSlow36 = (fSlow16 * cosf((fConst1 * fSlow35)));
		float 	fSlow37 = float(fslider6);
		float 	fSlow38 = (4.656613e-10f * faustpower<2>(fSlow37));
		float 	fSlow39 = (((391.99542f * (iSlow2 + iSlow3)) + ((4.4e+02f * (iSlow4 + iSlow12)) + (466.16376f * (iSlow1 + iSlow10)))) + (415.3047f * (iSlow11 + iSlow22)));
		float 	fSlow40 = (fSlow16 * cosf((fConst1 * fSlow39)));
		float 	fSlow41 = float(fslider7);
		float 	fSlow42 = (4.656613e-10f * faustpower<2>(fSlow41));
		float 	fSlow43 = (((493.8833f * (iSlow12 + (iSlow11 + iSlow21))) + ((466.16376f * iSlow2) + (4.4e+02f * (iSlow7 + iSlow3)))) + (523.25116f * (iSlow10 + (iSlow1 + iSlow4))));
		float 	fSlow44 = (fSlow16 * cosf((fConst1 * fSlow43)));
		float 	fSlow45 = float(fslider8);
		float 	fSlow46 = (4.656613e-10f * faustpower<2>(fSlow45));
		float 	fSlow47 = (((587.3295f * (iSlow4 + iSlow10)) + ((659.2551f * iSlow1) + (493.8833f * iSlow7))) + (523.25116f * (iSlow12 + (iSlow11 + (iSlow3 + (iSlow2 + iSlow21))))));
		float 	fSlow48 = (fSlow16 * cosf((fConst1 * fSlow47)));
		float 	fSlow49 = float(fslider9);
		float 	fSlow50 = (4.656613e-10f * faustpower<2>(fSlow49));
		float 	fSlow51 = (float(fslider11) + (0.3f * float(fslider10)));
		float 	fSlow52 = ((2 * fSlow51) + 1);
		float 	fSlow53 = powf(0.001f,(1.0f / float((fConst5 * fSlow14))));
		float 	fSlow54 = (0 - (2 * fSlow53));
		float 	fSlow55 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow13))));
		float 	fSlow56 = faustpower<2>(fSlow53);
		float 	fSlow57 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow23))));
		float 	fSlow58 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow27))));
		float 	fSlow59 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow31))));
		float 	fSlow60 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow35))));
		float 	fSlow61 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow39))));
		float 	fSlow62 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow43))));
		float 	fSlow63 = (fSlow54 * cosf((fConst1 * (fSlow52 * fSlow47))));
		float 	fSlow64 = ((4 * fSlow51) + 1);
		float 	fSlow65 = powf(0.001f,(1.0f / float((fConst6 * fSlow14))));
		float 	fSlow66 = (0 - (2 * fSlow65));
		float 	fSlow67 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow13))));
		float 	fSlow68 = faustpower<2>(fSlow65);
		float 	fSlow69 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow23))));
		float 	fSlow70 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow27))));
		float 	fSlow71 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow31))));
		float 	fSlow72 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow35))));
		float 	fSlow73 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow39))));
		float 	fSlow74 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow43))));
		float 	fSlow75 = (fSlow66 * cosf((fConst1 * (fSlow64 * fSlow47))));
		float 	fSlow76 = ((6 * fSlow51) + 1);
		float 	fSlow77 = powf(0.001f,(1.0f / float((fConst7 * fSlow14))));
		float 	fSlow78 = (0 - (2 * fSlow77));
		float 	fSlow79 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow13))));
		float 	fSlow80 = faustpower<2>(fSlow77);
		float 	fSlow81 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow23))));
		float 	fSlow82 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow27))));
		float 	fSlow83 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow31))));
		float 	fSlow84 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow35))));
		float 	fSlow85 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow39))));
		float 	fSlow86 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow43))));
		float 	fSlow87 = (fSlow78 * cosf((fConst1 * (fSlow76 * fSlow47))));
		float 	fSlow88 = ((8 * fSlow51) + 1);
		float 	fSlow89 = powf(0.001f,(1.0f / float((fConst8 * fSlow14))));
		float 	fSlow90 = (0 - (2 * fSlow89));
		float 	fSlow91 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow13))));
		float 	fSlow92 = faustpower<2>(fSlow89);
		float 	fSlow93 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow23))));
		float 	fSlow94 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow27))));
		float 	fSlow95 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow31))));
		float 	fSlow96 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow35))));
		float 	fSlow97 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow39))));
		float 	fSlow98 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow43))));
		float 	fSlow99 = (fSlow90 * cosf((fConst1 * (fSlow88 * fSlow47))));
		float 	fSlow100 = ((10 * fSlow51) + 1);
		float 	fSlow101 = powf(0.001f,(1.0f / float((fConst9 * fSlow14))));
		float 	fSlow102 = (0 - (2 * fSlow101));
		float 	fSlow103 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow13))));
		float 	fSlow104 = faustpower<2>(fSlow101);
		float 	fSlow105 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow23))));
		float 	fSlow106 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow27))));
		float 	fSlow107 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow31))));
		float 	fSlow108 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow35))));
		float 	fSlow109 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow39))));
		float 	fSlow110 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow43))));
		float 	fSlow111 = (fSlow102 * cosf((fConst1 * (fSlow100 * fSlow47))));
		float 	fSlow112 = ((12 * fSlow51) + 1);
		float 	fSlow113 = powf(0.001f,(1.0f / float((fConst10 * fSlow14))));
		float 	fSlow114 = (0 - (2 * fSlow113));
		float 	fSlow115 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow13))));
		float 	fSlow116 = faustpower<2>(fSlow113);
		float 	fSlow117 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow23))));
		float 	fSlow118 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow27))));
		float 	fSlow119 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow31))));
		float 	fSlow120 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow35))));
		float 	fSlow121 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow39))));
		float 	fSlow122 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow43))));
		float 	fSlow123 = (fSlow114 * cosf((fConst1 * (fSlow112 * fSlow47))));
		float 	fSlow124 = ((14 * fSlow51) + 1);
		float 	fSlow125 = powf(0.001f,(1.0f / float((fConst11 * fSlow14))));
		float 	fSlow126 = (0 - (2 * fSlow125));
		float 	fSlow127 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow13))));
		float 	fSlow128 = faustpower<2>(fSlow125);
		float 	fSlow129 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow23))));
		float 	fSlow130 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow27))));
		float 	fSlow131 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow31))));
		float 	fSlow132 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow35))));
		float 	fSlow133 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow39))));
		float 	fSlow134 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow43))));
		float 	fSlow135 = (fSlow126 * cosf((fConst1 * (fSlow124 * fSlow47))));
		float 	fSlow136 = ((16 * fSlow51) + 1);
		float 	fSlow137 = powf(0.001f,(1.0f / float((fConst12 * fSlow14))));
		float 	fSlow138 = (0 - (2 * fSlow137));
		float 	fSlow139 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow13))));
		float 	fSlow140 = faustpower<2>(fSlow137);
		float 	fSlow141 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow23))));
		float 	fSlow142 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow27))));
		float 	fSlow143 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow31))));
		float 	fSlow144 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow35))));
		float 	fSlow145 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow39))));
		float 	fSlow146 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow43))));
		float 	fSlow147 = (fSlow138 * cosf((fConst1 * (fSlow136 * fSlow47))));
		float 	fSlow148 = ((18 * fSlow51) + 1);
		float 	fSlow149 = powf(0.001f,(1.0f / float((fConst13 * fSlow14))));
		float 	fSlow150 = (0 - (2 * fSlow149));
		float 	fSlow151 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow13))));
		float 	fSlow152 = faustpower<2>(fSlow149);
		float 	fSlow153 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow23))));
		float 	fSlow154 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow27))));
		float 	fSlow155 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow31))));
		float 	fSlow156 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow35))));
		float 	fSlow157 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow39))));
		float 	fSlow158 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow43))));
		float 	fSlow159 = (fSlow150 * cosf((fConst1 * (fSlow148 * fSlow47))));
		float 	fSlow160 = ((20 * fSlow51) + 1);
		float 	fSlow161 = powf(0.001f,(1.0f / float((fConst14 * fSlow14))));
		float 	fSlow162 = (0 - (2 * fSlow161));
		float 	fSlow163 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow13))));
		float 	fSlow164 = faustpower<2>(fSlow161);
		float 	fSlow165 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow23))));
		float 	fSlow166 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow27))));
		float 	fSlow167 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow31))));
		float 	fSlow168 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow35))));
		float 	fSlow169 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow39))));
		float 	fSlow170 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow43))));
		float 	fSlow171 = (fSlow162 * cosf((fConst1 * (fSlow160 * fSlow47))));
		float 	fSlow172 = ((22 * fSlow51) + 1);
		float 	fSlow173 = powf(0.001f,(1.0f / float((fConst15 * fSlow14))));
		float 	fSlow174 = (0 - (2 * fSlow173));
		float 	fSlow175 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow13))));
		float 	fSlow176 = faustpower<2>(fSlow173);
		float 	fSlow177 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow23))));
		float 	fSlow178 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow27))));
		float 	fSlow179 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow31))));
		float 	fSlow180 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow35))));
		float 	fSlow181 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow39))));
		float 	fSlow182 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow43))));
		float 	fSlow183 = (fSlow174 * cosf((fConst1 * (fSlow172 * fSlow47))));
		float 	fSlow184 = ((24 * fSlow51) + 1);
		float 	fSlow185 = powf(0.001f,(1.0f / float((fConst16 * fSlow14))));
		float 	fSlow186 = (0 - (2 * fSlow185));
		float 	fSlow187 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow13))));
		float 	fSlow188 = faustpower<2>(fSlow185);
		float 	fSlow189 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow23))));
		float 	fSlow190 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow27))));
		float 	fSlow191 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow31))));
		float 	fSlow192 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow35))));
		float 	fSlow193 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow39))));
		float 	fSlow194 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow43))));
		float 	fSlow195 = (fSlow186 * cosf((fConst1 * (fSlow184 * fSlow47))));
		float 	fSlow196 = ((26 * fSlow51) + 1);
		float 	fSlow197 = powf(0.001f,(1.0f / float((fConst17 * fSlow14))));
		float 	fSlow198 = (0 - (2 * fSlow197));
		float 	fSlow199 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow13))));
		float 	fSlow200 = faustpower<2>(fSlow197);
		float 	fSlow201 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow23))));
		float 	fSlow202 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow27))));
		float 	fSlow203 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow31))));
		float 	fSlow204 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow35))));
		float 	fSlow205 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow39))));
		float 	fSlow206 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow43))));
		float 	fSlow207 = (fSlow198 * cosf((fConst1 * (fSlow196 * fSlow47))));
		float 	fSlow208 = ((28 * fSlow51) + 1);
		float 	fSlow209 = powf(0.001f,(1.0f / float((fConst18 * fSlow14))));
		float 	fSlow210 = (0 - (2 * fSlow209));
		float 	fSlow211 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow13))));
		float 	fSlow212 = faustpower<2>(fSlow209);
		float 	fSlow213 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow23))));
		float 	fSlow214 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow27))));
		float 	fSlow215 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow31))));
		float 	fSlow216 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow35))));
		float 	fSlow217 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow39))));
		float 	fSlow218 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow43))));
		float 	fSlow219 = (fSlow210 * cosf((fConst1 * (fSlow208 * fSlow47))));
		float 	fSlow220 = ((30 * fSlow51) + 1);
		float 	fSlow221 = powf(0.001f,(1.0f / float((fConst19 * fSlow14))));
		float 	fSlow222 = (0 - (2 * fSlow221));
		float 	fSlow223 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow13))));
		float 	fSlow224 = faustpower<2>(fSlow221);
		float 	fSlow225 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow23))));
		float 	fSlow226 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow27))));
		float 	fSlow227 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow31))));
		float 	fSlow228 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow35))));
		float 	fSlow229 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow39))));
		float 	fSlow230 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow43))));
		float 	fSlow231 = (fSlow222 * cosf((fConst1 * (fSlow220 * fSlow47))));
		float 	fSlow232 = ((32 * fSlow51) + 1);
		float 	fSlow233 = powf(0.001f,(1.0f / float((fConst20 * fSlow14))));
		float 	fSlow234 = (0 - (2 * fSlow233));
		float 	fSlow235 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow13))));
		float 	fSlow236 = faustpower<2>(fSlow233);
		float 	fSlow237 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow23))));
		float 	fSlow238 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow27))));
		float 	fSlow239 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow31))));
		float 	fSlow240 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow35))));
		float 	fSlow241 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow39))));
		float 	fSlow242 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow43))));
		float 	fSlow243 = (fSlow234 * cosf((fConst1 * (fSlow232 * fSlow47))));
		float 	fSlow244 = ((34 * fSlow51) + 1);
		float 	fSlow245 = powf(0.001f,(1.0f / float((fConst21 * fSlow14))));
		float 	fSlow246 = (0 - (2 * fSlow245));
		float 	fSlow247 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow13))));
		float 	fSlow248 = faustpower<2>(fSlow245);
		float 	fSlow249 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow23))));
		float 	fSlow250 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow27))));
		float 	fSlow251 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow31))));
		float 	fSlow252 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow35))));
		float 	fSlow253 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow39))));
		float 	fSlow254 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow43))));
		float 	fSlow255 = (fSlow246 * cosf((fConst1 * (fSlow244 * fSlow47))));
		float 	fSlow256 = ((36 * fSlow51) + 1);
		float 	fSlow257 = powf(0.001f,(1.0f / float((fConst22 * fSlow14))));
		float 	fSlow258 = (0 - (2 * fSlow257));
		float 	fSlow259 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow13))));
		float 	fSlow260 = faustpower<2>(fSlow257);
		float 	fSlow261 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow23))));
		float 	fSlow262 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow27))));
		float 	fSlow263 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow31))));
		float 	fSlow264 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow35))));
		float 	fSlow265 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow39))));
		float 	fSlow266 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow43))));
		float 	fSlow267 = (fSlow258 * cosf((fConst1 * (fSlow256 * fSlow47))));
		float 	fSlow268 = ((38 * fSlow51) + 1);
		float 	fSlow269 = powf(0.001f,(1.0f / float((fConst23 * fSlow14))));
		float 	fSlow270 = (0 - (2 * fSlow269));
		float 	fSlow271 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow13))));
		float 	fSlow272 = faustpower<2>(fSlow269);
		float 	fSlow273 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow23))));
		float 	fSlow274 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow27))));
		float 	fSlow275 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow31))));
		float 	fSlow276 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow35))));
		float 	fSlow277 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow39))));
		float 	fSlow278 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow43))));
		float 	fSlow279 = (fSlow270 * cosf((fConst1 * (fSlow268 * fSlow47))));
		float 	fSlow280 = ((40 * fSlow51) + 1);
		float 	fSlow281 = powf(0.001f,(1.0f / float((fConst24 * fSlow14))));
		float 	fSlow282 = (0 - (2 * fSlow281));
		float 	fSlow283 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow13))));
		float 	fSlow284 = faustpower<2>(fSlow281);
		float 	fSlow285 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow23))));
		float 	fSlow286 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow27))));
		float 	fSlow287 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow31))));
		float 	fSlow288 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow35))));
		float 	fSlow289 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow39))));
		float 	fSlow290 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow43))));
		float 	fSlow291 = (fSlow282 * cosf((fConst1 * (fSlow280 * fSlow47))));
		float 	fSlow292 = ((42 * fSlow51) + 1);
		float 	fSlow293 = powf(0.001f,(1.0f / float((fConst25 * fSlow14))));
		float 	fSlow294 = (0 - (2 * fSlow293));
		float 	fSlow295 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow13))));
		float 	fSlow296 = faustpower<2>(fSlow293);
		float 	fSlow297 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow23))));
		float 	fSlow298 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow27))));
		float 	fSlow299 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow31))));
		float 	fSlow300 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow35))));
		float 	fSlow301 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow39))));
		float 	fSlow302 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow43))));
		float 	fSlow303 = (fSlow294 * cosf((fConst1 * (fSlow292 * fSlow47))));
		float 	fSlow304 = ((44 * fSlow51) + 1);
		float 	fSlow305 = powf(0.001f,(1.0f / float((fConst26 * fSlow14))));
		float 	fSlow306 = (0 - (2 * fSlow305));
		float 	fSlow307 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow13))));
		float 	fSlow308 = faustpower<2>(fSlow305);
		float 	fSlow309 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow23))));
		float 	fSlow310 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow27))));
		float 	fSlow311 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow31))));
		float 	fSlow312 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow35))));
		float 	fSlow313 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow39))));
		float 	fSlow314 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow43))));
		float 	fSlow315 = (fSlow306 * cosf((fConst1 * (fSlow304 * fSlow47))));
		float 	fSlow316 = ((46 * fSlow51) + 1);
		float 	fSlow317 = powf(0.001f,(1.0f / float((fConst27 * fSlow14))));
		float 	fSlow318 = (0 - (2 * fSlow317));
		float 	fSlow319 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow13))));
		float 	fSlow320 = faustpower<2>(fSlow317);
		float 	fSlow321 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow23))));
		float 	fSlow322 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow27))));
		float 	fSlow323 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow31))));
		float 	fSlow324 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow35))));
		float 	fSlow325 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow39))));
		float 	fSlow326 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow43))));
		float 	fSlow327 = (fSlow318 * cosf((fConst1 * (fSlow316 * fSlow47))));
		float 	fSlow328 = ((48 * fSlow51) + 1);
		float 	fSlow329 = powf(0.001f,(1.0f / float((fConst28 * fSlow14))));
		float 	fSlow330 = (0 - (2 * fSlow329));
		float 	fSlow331 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow13))));
		float 	fSlow332 = faustpower<2>(fSlow329);
		float 	fSlow333 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow23))));
		float 	fSlow334 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow27))));
		float 	fSlow335 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow31))));
		float 	fSlow336 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow35))));
		float 	fSlow337 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow39))));
		float 	fSlow338 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow43))));
		float 	fSlow339 = (fSlow330 * cosf((fConst1 * (fSlow328 * fSlow47))));
		float 	fSlow340 = ((50 * fSlow51) + 1);
		float 	fSlow341 = powf(0.001f,(1.0f / float((fConst29 * fSlow14))));
		float 	fSlow342 = (0 - (2 * fSlow341));
		float 	fSlow343 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow13))));
		float 	fSlow344 = faustpower<2>(fSlow341);
		float 	fSlow345 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow23))));
		float 	fSlow346 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow27))));
		float 	fSlow347 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow31))));
		float 	fSlow348 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow35))));
		float 	fSlow349 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow39))));
		float 	fSlow350 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow43))));
		float 	fSlow351 = (fSlow342 * cosf((fConst1 * (fSlow340 * fSlow47))));
		float 	fSlow352 = ((52 * fSlow51) + 1);
		float 	fSlow353 = powf(0.001f,(1.0f / float((fConst30 * fSlow14))));
		float 	fSlow354 = (0 - (2 * fSlow353));
		float 	fSlow355 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow13))));
		float 	fSlow356 = faustpower<2>(fSlow353);
		float 	fSlow357 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow23))));
		float 	fSlow358 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow27))));
		float 	fSlow359 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow31))));
		float 	fSlow360 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow35))));
		float 	fSlow361 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow39))));
		float 	fSlow362 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow43))));
		float 	fSlow363 = (fSlow354 * cosf((fConst1 * (fSlow352 * fSlow47))));
		float 	fSlow364 = ((54 * fSlow51) + 1);
		float 	fSlow365 = powf(0.001f,(1.0f / float((fConst31 * fSlow14))));
		float 	fSlow366 = (0 - (2 * fSlow365));
		float 	fSlow367 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow13))));
		float 	fSlow368 = faustpower<2>(fSlow365);
		float 	fSlow369 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow23))));
		float 	fSlow370 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow27))));
		float 	fSlow371 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow31))));
		float 	fSlow372 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow35))));
		float 	fSlow373 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow39))));
		float 	fSlow374 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow43))));
		float 	fSlow375 = (fSlow366 * cosf((fConst1 * (fSlow364 * fSlow47))));
		float 	fSlow376 = ((56 * fSlow51) + 1);
		float 	fSlow377 = powf(0.001f,(1.0f / float((fConst32 * fSlow14))));
		float 	fSlow378 = (0 - (2 * fSlow377));
		float 	fSlow379 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow13))));
		float 	fSlow380 = faustpower<2>(fSlow377);
		float 	fSlow381 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow23))));
		float 	fSlow382 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow27))));
		float 	fSlow383 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow31))));
		float 	fSlow384 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow35))));
		float 	fSlow385 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow39))));
		float 	fSlow386 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow43))));
		float 	fSlow387 = (fSlow378 * cosf((fConst1 * (fSlow376 * fSlow47))));
		float 	fSlow388 = ((58 * fSlow51) + 1);
		float 	fSlow389 = powf(0.001f,(1.0f / float((fConst33 * fSlow14))));
		float 	fSlow390 = (0 - (2 * fSlow389));
		float 	fSlow391 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow13))));
		float 	fSlow392 = faustpower<2>(fSlow389);
		float 	fSlow393 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow23))));
		float 	fSlow394 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow27))));
		float 	fSlow395 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow31))));
		float 	fSlow396 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow35))));
		float 	fSlow397 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow39))));
		float 	fSlow398 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow43))));
		float 	fSlow399 = (fSlow390 * cosf((fConst1 * (fSlow388 * fSlow47))));
		float 	fSlow400 = float(fslider12);
		int 	iSlow401 = int((int((int((fConst0 * float(fslider13))) & 65535)) + 1));
		float 	fSlow402 = float(fslider14);
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fVec0[0] = fSlow19;
			int iTemp0 = ((fSlow19 - fVec0[1]) > 0);
			iVec1[0] = iTemp0;
			fRec3[0] = ((int((((iVec1[0] - iVec1[1]) == 1) > 0)))?0:min(fConst2, (fRec3[1] + 1)));
			int iTemp1 = int((fRec3[0] < fConst3));
			iRec4[0] = ((1103515245 * iRec4[1]) + 12345);
			float fTemp2 = (fSlow20 * (iRec4[0] * ((iTemp1)?((int((fRec3[0] < 0)))?0:((iTemp1)?(fConst4 * fRec3[0]):1)):((int((fRec3[0] < fConst2)))?((fConst4 * (fConst3 - fRec3[0])) + 1):0))));
			fRec2[0] = (fTemp2 - ((fSlow18 * fRec2[2]) + (fSlow17 * fRec2[1])));
			fVec2[0] = fSlow25;
			int iTemp3 = ((fSlow25 - fVec2[1]) > 0);
			iVec3[0] = iTemp3;
			fRec6[0] = ((int((((iVec3[0] - iVec3[1]) == 1) > 0)))?0:min(fConst2, (fRec6[1] + 1)));
			int iTemp4 = int((fRec6[0] < fConst3));
			float fTemp5 = (fSlow26 * (iRec4[0] * ((iTemp4)?((int((fRec6[0] < 0)))?0:((iTemp4)?(fConst4 * fRec6[0]):1)):((int((fRec6[0] < fConst2)))?((fConst4 * (fConst3 - fRec6[0])) + 1):0))));
			fRec5[0] = (fTemp5 - ((fSlow18 * fRec5[2]) + (fSlow24 * fRec5[1])));
			fVec4[0] = fSlow29;
			int iTemp6 = ((fSlow29 - fVec4[1]) > 0);
			iVec5[0] = iTemp6;
			fRec8[0] = ((int((((iVec5[0] - iVec5[1]) == 1) > 0)))?0:min(fConst2, (fRec8[1] + 1)));
			int iTemp7 = int((fRec8[0] < fConst3));
			float fTemp8 = (fSlow30 * (iRec4[0] * ((iTemp7)?((int((fRec8[0] < 0)))?0:((iTemp7)?(fConst4 * fRec8[0]):1)):((int((fRec8[0] < fConst2)))?((fConst4 * (fConst3 - fRec8[0])) + 1):0))));
			fRec7[0] = (fTemp8 - ((fSlow18 * fRec7[2]) + (fSlow28 * fRec7[1])));
			fVec6[0] = fSlow33;
			int iTemp9 = ((fSlow33 - fVec6[1]) > 0);
			iVec7[0] = iTemp9;
			fRec10[0] = ((int((((iVec7[0] - iVec7[1]) == 1) > 0)))?0:min(fConst2, (fRec10[1] + 1)));
			int iTemp10 = int((fRec10[0] < fConst3));
			float fTemp11 = (fSlow34 * (iRec4[0] * ((iTemp10)?((int((fRec10[0] < 0)))?0:((iTemp10)?(fConst4 * fRec10[0]):1)):((int((fRec10[0] < fConst2)))?((fConst4 * (fConst3 - fRec10[0])) + 1):0))));
			fRec9[0] = (fTemp11 - ((fSlow18 * fRec9[2]) + (fSlow32 * fRec9[1])));
			fVec8[0] = fSlow37;
			int iTemp12 = ((fSlow37 - fVec8[1]) > 0);
			iVec9[0] = iTemp12;
			fRec12[0] = ((int((((iVec9[0] - iVec9[1]) == 1) > 0)))?0:min(fConst2, (fRec12[1] + 1)));
			int iTemp13 = int((fRec12[0] < fConst3));
			float fTemp14 = (fSlow38 * (iRec4[0] * ((iTemp13)?((int((fRec12[0] < 0)))?0:((iTemp13)?(fConst4 * fRec12[0]):1)):((int((fRec12[0] < fConst2)))?((fConst4 * (fConst3 - fRec12[0])) + 1):0))));
			fRec11[0] = (fTemp14 - ((fSlow18 * fRec11[2]) + (fSlow36 * fRec11[1])));
			fVec10[0] = fSlow41;
			int iTemp15 = ((fSlow41 - fVec10[1]) > 0);
			iVec11[0] = iTemp15;
			fRec14[0] = ((int((((iVec11[0] - iVec11[1]) == 1) > 0)))?0:min(fConst2, (fRec14[1] + 1)));
			int iTemp16 = int((fRec14[0] < fConst3));
			float fTemp17 = (fSlow42 * (iRec4[0] * ((iTemp16)?((int((fRec14[0] < 0)))?0:((iTemp16)?(fConst4 * fRec14[0]):1)):((int((fRec14[0] < fConst2)))?((fConst4 * (fConst3 - fRec14[0])) + 1):0))));
			fRec13[0] = (fTemp17 - ((fSlow18 * fRec13[2]) + (fSlow40 * fRec13[1])));
			fVec12[0] = fSlow45;
			int iTemp18 = ((fSlow45 - fVec12[1]) > 0);
			iVec13[0] = iTemp18;
			fRec16[0] = ((int((((iVec13[0] - iVec13[1]) == 1) > 0)))?0:min(fConst2, (fRec16[1] + 1)));
			int iTemp19 = int((fRec16[0] < fConst3));
			float fTemp20 = (fSlow46 * (iRec4[0] * ((iTemp19)?((int((fRec16[0] < 0)))?0:((iTemp19)?(fConst4 * fRec16[0]):1)):((int((fRec16[0] < fConst2)))?((fConst4 * (fConst3 - fRec16[0])) + 1):0))));
			fRec15[0] = (fTemp20 - ((fSlow18 * fRec15[2]) + (fSlow44 * fRec15[1])));
			fVec14[0] = fSlow49;
			int iTemp21 = ((fSlow49 - fVec14[1]) > 0);
			iVec15[0] = iTemp21;
			fRec18[0] = ((int((((iVec15[0] - iVec15[1]) == 1) > 0)))?0:min(fConst2, (fRec18[1] + 1)));
			int iTemp22 = int((fRec18[0] < fConst3));
			float fTemp23 = (fSlow50 * (iRec4[0] * ((iTemp22)?((int((fRec18[0] < 0)))?0:((iTemp22)?(fConst4 * fRec18[0]):1)):((int((fRec18[0] < fConst2)))?((fConst4 * (fConst3 - fRec18[0])) + 1):0))));
			fRec17[0] = (fTemp23 - ((fSlow18 * fRec17[2]) + (fSlow48 * fRec17[1])));
			fRec19[0] = (fTemp2 - ((fSlow56 * fRec19[2]) + (fSlow55 * fRec19[1])));
			fRec20[0] = (fTemp5 - ((fSlow56 * fRec20[2]) + (fSlow57 * fRec20[1])));
			fRec21[0] = (fTemp8 - ((fSlow56 * fRec21[2]) + (fSlow58 * fRec21[1])));
			fRec22[0] = (fTemp11 - ((fSlow56 * fRec22[2]) + (fSlow59 * fRec22[1])));
			fRec23[0] = (fTemp14 - ((fSlow56 * fRec23[2]) + (fSlow60 * fRec23[1])));
			fRec24[0] = (fTemp17 - ((fSlow56 * fRec24[2]) + (fSlow61 * fRec24[1])));
			fRec25[0] = (fTemp20 - ((fSlow56 * fRec25[2]) + (fSlow62 * fRec25[1])));
			fRec26[0] = (fTemp23 - ((fSlow56 * fRec26[2]) + (fSlow63 * fRec26[1])));
			fRec27[0] = (fTemp2 - ((fSlow68 * fRec27[2]) + (fSlow67 * fRec27[1])));
			fRec28[0] = (fTemp5 - ((fSlow68 * fRec28[2]) + (fSlow69 * fRec28[1])));
			fRec29[0] = (fTemp8 - ((fSlow68 * fRec29[2]) + (fSlow70 * fRec29[1])));
			fRec30[0] = (fTemp11 - ((fSlow68 * fRec30[2]) + (fSlow71 * fRec30[1])));
			fRec31[0] = (fTemp14 - ((fSlow68 * fRec31[2]) + (fSlow72 * fRec31[1])));
			fRec32[0] = (fTemp17 - ((fSlow68 * fRec32[2]) + (fSlow73 * fRec32[1])));
			fRec33[0] = (fTemp20 - ((fSlow68 * fRec33[2]) + (fSlow74 * fRec33[1])));
			fRec34[0] = (fTemp23 - ((fSlow68 * fRec34[2]) + (fSlow75 * fRec34[1])));
			fRec35[0] = (fTemp2 - ((fSlow80 * fRec35[2]) + (fSlow79 * fRec35[1])));
			fRec36[0] = (fTemp5 - ((fSlow80 * fRec36[2]) + (fSlow81 * fRec36[1])));
			fRec37[0] = (fTemp8 - ((fSlow80 * fRec37[2]) + (fSlow82 * fRec37[1])));
			fRec38[0] = (fTemp11 - ((fSlow80 * fRec38[2]) + (fSlow83 * fRec38[1])));
			fRec39[0] = (fTemp14 - ((fSlow80 * fRec39[2]) + (fSlow84 * fRec39[1])));
			fRec40[0] = (fTemp17 - ((fSlow80 * fRec40[2]) + (fSlow85 * fRec40[1])));
			fRec41[0] = (fTemp20 - ((fSlow80 * fRec41[2]) + (fSlow86 * fRec41[1])));
			fRec42[0] = (fTemp23 - ((fSlow80 * fRec42[2]) + (fSlow87 * fRec42[1])));
			fRec43[0] = (fTemp2 - ((fSlow92 * fRec43[2]) + (fSlow91 * fRec43[1])));
			fRec44[0] = (fTemp5 - ((fSlow92 * fRec44[2]) + (fSlow93 * fRec44[1])));
			fRec45[0] = (fTemp8 - ((fSlow92 * fRec45[2]) + (fSlow94 * fRec45[1])));
			fRec46[0] = (fTemp11 - ((fSlow92 * fRec46[2]) + (fSlow95 * fRec46[1])));
			fRec47[0] = (fTemp14 - ((fSlow92 * fRec47[2]) + (fSlow96 * fRec47[1])));
			fRec48[0] = (fTemp17 - ((fSlow92 * fRec48[2]) + (fSlow97 * fRec48[1])));
			fRec49[0] = (fTemp20 - ((fSlow92 * fRec49[2]) + (fSlow98 * fRec49[1])));
			fRec50[0] = (fTemp23 - ((fSlow92 * fRec50[2]) + (fSlow99 * fRec50[1])));
			fRec51[0] = (fTemp2 - ((fSlow104 * fRec51[2]) + (fSlow103 * fRec51[1])));
			fRec52[0] = (fTemp5 - ((fSlow104 * fRec52[2]) + (fSlow105 * fRec52[1])));
			fRec53[0] = (fTemp8 - ((fSlow104 * fRec53[2]) + (fSlow106 * fRec53[1])));
			fRec54[0] = (fTemp11 - ((fSlow104 * fRec54[2]) + (fSlow107 * fRec54[1])));
			fRec55[0] = (fTemp14 - ((fSlow104 * fRec55[2]) + (fSlow108 * fRec55[1])));
			fRec56[0] = (fTemp17 - ((fSlow104 * fRec56[2]) + (fSlow109 * fRec56[1])));
			fRec57[0] = (fTemp20 - ((fSlow104 * fRec57[2]) + (fSlow110 * fRec57[1])));
			fRec58[0] = (fTemp23 - ((fSlow104 * fRec58[2]) + (fSlow111 * fRec58[1])));
			fRec59[0] = (fTemp2 - ((fSlow116 * fRec59[2]) + (fSlow115 * fRec59[1])));
			fRec60[0] = (fTemp5 - ((fSlow116 * fRec60[2]) + (fSlow117 * fRec60[1])));
			fRec61[0] = (fTemp8 - ((fSlow116 * fRec61[2]) + (fSlow118 * fRec61[1])));
			fRec62[0] = (fTemp11 - ((fSlow116 * fRec62[2]) + (fSlow119 * fRec62[1])));
			fRec63[0] = (fTemp14 - ((fSlow116 * fRec63[2]) + (fSlow120 * fRec63[1])));
			fRec64[0] = (fTemp17 - ((fSlow116 * fRec64[2]) + (fSlow121 * fRec64[1])));
			fRec65[0] = (fTemp20 - ((fSlow116 * fRec65[2]) + (fSlow122 * fRec65[1])));
			fRec66[0] = (fTemp23 - ((fSlow116 * fRec66[2]) + (fSlow123 * fRec66[1])));
			fRec67[0] = (fTemp2 - ((fSlow128 * fRec67[2]) + (fSlow127 * fRec67[1])));
			fRec68[0] = (fTemp5 - ((fSlow128 * fRec68[2]) + (fSlow129 * fRec68[1])));
			fRec69[0] = (fTemp8 - ((fSlow128 * fRec69[2]) + (fSlow130 * fRec69[1])));
			fRec70[0] = (fTemp11 - ((fSlow128 * fRec70[2]) + (fSlow131 * fRec70[1])));
			fRec71[0] = (fTemp14 - ((fSlow128 * fRec71[2]) + (fSlow132 * fRec71[1])));
			fRec72[0] = (fTemp17 - ((fSlow128 * fRec72[2]) + (fSlow133 * fRec72[1])));
			fRec73[0] = (fTemp20 - ((fSlow128 * fRec73[2]) + (fSlow134 * fRec73[1])));
			fRec74[0] = (fTemp23 - ((fSlow128 * fRec74[2]) + (fSlow135 * fRec74[1])));
			fRec75[0] = (fTemp2 - ((fSlow140 * fRec75[2]) + (fSlow139 * fRec75[1])));
			fRec76[0] = (fTemp5 - ((fSlow140 * fRec76[2]) + (fSlow141 * fRec76[1])));
			fRec77[0] = (fTemp8 - ((fSlow140 * fRec77[2]) + (fSlow142 * fRec77[1])));
			fRec78[0] = (fTemp11 - ((fSlow140 * fRec78[2]) + (fSlow143 * fRec78[1])));
			fRec79[0] = (fTemp14 - ((fSlow140 * fRec79[2]) + (fSlow144 * fRec79[1])));
			fRec80[0] = (fTemp17 - ((fSlow140 * fRec80[2]) + (fSlow145 * fRec80[1])));
			fRec81[0] = (fTemp20 - ((fSlow140 * fRec81[2]) + (fSlow146 * fRec81[1])));
			fRec82[0] = (fTemp23 - ((fSlow140 * fRec82[2]) + (fSlow147 * fRec82[1])));
			fRec83[0] = (fTemp2 - ((fSlow152 * fRec83[2]) + (fSlow151 * fRec83[1])));
			fRec84[0] = (fTemp5 - ((fSlow152 * fRec84[2]) + (fSlow153 * fRec84[1])));
			fRec85[0] = (fTemp8 - ((fSlow152 * fRec85[2]) + (fSlow154 * fRec85[1])));
			fRec86[0] = (fTemp11 - ((fSlow152 * fRec86[2]) + (fSlow155 * fRec86[1])));
			fRec87[0] = (fTemp14 - ((fSlow152 * fRec87[2]) + (fSlow156 * fRec87[1])));
			fRec88[0] = (fTemp17 - ((fSlow152 * fRec88[2]) + (fSlow157 * fRec88[1])));
			fRec89[0] = (fTemp20 - ((fSlow152 * fRec89[2]) + (fSlow158 * fRec89[1])));
			fRec90[0] = (fTemp23 - ((fSlow152 * fRec90[2]) + (fSlow159 * fRec90[1])));
			fRec91[0] = (fTemp2 - ((fSlow164 * fRec91[2]) + (fSlow163 * fRec91[1])));
			fRec92[0] = (fTemp5 - ((fSlow164 * fRec92[2]) + (fSlow165 * fRec92[1])));
			fRec93[0] = (fTemp8 - ((fSlow164 * fRec93[2]) + (fSlow166 * fRec93[1])));
			fRec94[0] = (fTemp11 - ((fSlow164 * fRec94[2]) + (fSlow167 * fRec94[1])));
			fRec95[0] = (fTemp14 - ((fSlow164 * fRec95[2]) + (fSlow168 * fRec95[1])));
			fRec96[0] = (fTemp17 - ((fSlow164 * fRec96[2]) + (fSlow169 * fRec96[1])));
			fRec97[0] = (fTemp20 - ((fSlow164 * fRec97[2]) + (fSlow170 * fRec97[1])));
			fRec98[0] = (fTemp23 - ((fSlow164 * fRec98[2]) + (fSlow171 * fRec98[1])));
			fRec99[0] = (fTemp2 - ((fSlow176 * fRec99[2]) + (fSlow175 * fRec99[1])));
			fRec100[0] = (fTemp5 - ((fSlow176 * fRec100[2]) + (fSlow177 * fRec100[1])));
			fRec101[0] = (fTemp8 - ((fSlow176 * fRec101[2]) + (fSlow178 * fRec101[1])));
			fRec102[0] = (fTemp11 - ((fSlow176 * fRec102[2]) + (fSlow179 * fRec102[1])));
			fRec103[0] = (fTemp14 - ((fSlow176 * fRec103[2]) + (fSlow180 * fRec103[1])));
			fRec104[0] = (fTemp17 - ((fSlow176 * fRec104[2]) + (fSlow181 * fRec104[1])));
			fRec105[0] = (fTemp20 - ((fSlow176 * fRec105[2]) + (fSlow182 * fRec105[1])));
			fRec106[0] = (fTemp23 - ((fSlow176 * fRec106[2]) + (fSlow183 * fRec106[1])));
			fRec107[0] = (fTemp2 - ((fSlow188 * fRec107[2]) + (fSlow187 * fRec107[1])));
			fRec108[0] = (fTemp5 - ((fSlow188 * fRec108[2]) + (fSlow189 * fRec108[1])));
			fRec109[0] = (fTemp8 - ((fSlow188 * fRec109[2]) + (fSlow190 * fRec109[1])));
			fRec110[0] = (fTemp11 - ((fSlow188 * fRec110[2]) + (fSlow191 * fRec110[1])));
			fRec111[0] = (fTemp14 - ((fSlow188 * fRec111[2]) + (fSlow192 * fRec111[1])));
			fRec112[0] = (fTemp17 - ((fSlow188 * fRec112[2]) + (fSlow193 * fRec112[1])));
			fRec113[0] = (fTemp20 - ((fSlow188 * fRec113[2]) + (fSlow194 * fRec113[1])));
			fRec114[0] = (fTemp23 - ((fSlow188 * fRec114[2]) + (fSlow195 * fRec114[1])));
			fRec115[0] = (fTemp2 - ((fSlow200 * fRec115[2]) + (fSlow199 * fRec115[1])));
			fRec116[0] = (fTemp5 - ((fSlow200 * fRec116[2]) + (fSlow201 * fRec116[1])));
			fRec117[0] = (fTemp8 - ((fSlow200 * fRec117[2]) + (fSlow202 * fRec117[1])));
			fRec118[0] = (fTemp11 - ((fSlow200 * fRec118[2]) + (fSlow203 * fRec118[1])));
			fRec119[0] = (fTemp14 - ((fSlow200 * fRec119[2]) + (fSlow204 * fRec119[1])));
			fRec120[0] = (fTemp17 - ((fSlow200 * fRec120[2]) + (fSlow205 * fRec120[1])));
			fRec121[0] = (fTemp20 - ((fSlow200 * fRec121[2]) + (fSlow206 * fRec121[1])));
			fRec122[0] = (fTemp23 - ((fSlow200 * fRec122[2]) + (fSlow207 * fRec122[1])));
			fRec123[0] = (fTemp2 - ((fSlow212 * fRec123[2]) + (fSlow211 * fRec123[1])));
			fRec124[0] = (fTemp5 - ((fSlow212 * fRec124[2]) + (fSlow213 * fRec124[1])));
			fRec125[0] = (fTemp8 - ((fSlow212 * fRec125[2]) + (fSlow214 * fRec125[1])));
			fRec126[0] = (fTemp11 - ((fSlow212 * fRec126[2]) + (fSlow215 * fRec126[1])));
			fRec127[0] = (fTemp14 - ((fSlow212 * fRec127[2]) + (fSlow216 * fRec127[1])));
			fRec128[0] = (fTemp17 - ((fSlow212 * fRec128[2]) + (fSlow217 * fRec128[1])));
			fRec129[0] = (fTemp20 - ((fSlow212 * fRec129[2]) + (fSlow218 * fRec129[1])));
			fRec130[0] = (fTemp23 - ((fSlow212 * fRec130[2]) + (fSlow219 * fRec130[1])));
			fRec131[0] = (fTemp2 - ((fSlow224 * fRec131[2]) + (fSlow223 * fRec131[1])));
			fRec132[0] = (fTemp5 - ((fSlow224 * fRec132[2]) + (fSlow225 * fRec132[1])));
			fRec133[0] = (fTemp8 - ((fSlow224 * fRec133[2]) + (fSlow226 * fRec133[1])));
			fRec134[0] = (fTemp11 - ((fSlow224 * fRec134[2]) + (fSlow227 * fRec134[1])));
			fRec135[0] = (fTemp14 - ((fSlow224 * fRec135[2]) + (fSlow228 * fRec135[1])));
			fRec136[0] = (fTemp17 - ((fSlow224 * fRec136[2]) + (fSlow229 * fRec136[1])));
			fRec137[0] = (fTemp20 - ((fSlow224 * fRec137[2]) + (fSlow230 * fRec137[1])));
			fRec138[0] = (fTemp23 - ((fSlow224 * fRec138[2]) + (fSlow231 * fRec138[1])));
			fRec139[0] = (fTemp2 - ((fSlow236 * fRec139[2]) + (fSlow235 * fRec139[1])));
			fRec140[0] = (fTemp5 - ((fSlow236 * fRec140[2]) + (fSlow237 * fRec140[1])));
			fRec141[0] = (fTemp8 - ((fSlow236 * fRec141[2]) + (fSlow238 * fRec141[1])));
			fRec142[0] = (fTemp11 - ((fSlow236 * fRec142[2]) + (fSlow239 * fRec142[1])));
			fRec143[0] = (fTemp14 - ((fSlow236 * fRec143[2]) + (fSlow240 * fRec143[1])));
			fRec144[0] = (fTemp17 - ((fSlow236 * fRec144[2]) + (fSlow241 * fRec144[1])));
			fRec145[0] = (fTemp20 - ((fSlow236 * fRec145[2]) + (fSlow242 * fRec145[1])));
			fRec146[0] = (fTemp23 - ((fSlow236 * fRec146[2]) + (fSlow243 * fRec146[1])));
			fRec147[0] = (fTemp2 - ((fSlow248 * fRec147[2]) + (fSlow247 * fRec147[1])));
			fRec148[0] = (fTemp5 - ((fSlow248 * fRec148[2]) + (fSlow249 * fRec148[1])));
			fRec149[0] = (fTemp8 - ((fSlow248 * fRec149[2]) + (fSlow250 * fRec149[1])));
			fRec150[0] = (fTemp11 - ((fSlow248 * fRec150[2]) + (fSlow251 * fRec150[1])));
			fRec151[0] = (fTemp14 - ((fSlow248 * fRec151[2]) + (fSlow252 * fRec151[1])));
			fRec152[0] = (fTemp17 - ((fSlow248 * fRec152[2]) + (fSlow253 * fRec152[1])));
			fRec153[0] = (fTemp20 - ((fSlow248 * fRec153[2]) + (fSlow254 * fRec153[1])));
			fRec154[0] = (fTemp23 - ((fSlow248 * fRec154[2]) + (fSlow255 * fRec154[1])));
			fRec155[0] = (fTemp2 - ((fSlow260 * fRec155[2]) + (fSlow259 * fRec155[1])));
			fRec156[0] = (fTemp5 - ((fSlow260 * fRec156[2]) + (fSlow261 * fRec156[1])));
			fRec157[0] = (fTemp8 - ((fSlow260 * fRec157[2]) + (fSlow262 * fRec157[1])));
			fRec158[0] = (fTemp11 - ((fSlow260 * fRec158[2]) + (fSlow263 * fRec158[1])));
			fRec159[0] = (fTemp14 - ((fSlow260 * fRec159[2]) + (fSlow264 * fRec159[1])));
			fRec160[0] = (fTemp17 - ((fSlow260 * fRec160[2]) + (fSlow265 * fRec160[1])));
			fRec161[0] = (fTemp20 - ((fSlow260 * fRec161[2]) + (fSlow266 * fRec161[1])));
			fRec162[0] = (fTemp23 - ((fSlow260 * fRec162[2]) + (fSlow267 * fRec162[1])));
			fRec163[0] = (fTemp2 - ((fSlow272 * fRec163[2]) + (fSlow271 * fRec163[1])));
			fRec164[0] = (fTemp5 - ((fSlow272 * fRec164[2]) + (fSlow273 * fRec164[1])));
			fRec165[0] = (fTemp8 - ((fSlow272 * fRec165[2]) + (fSlow274 * fRec165[1])));
			fRec166[0] = (fTemp11 - ((fSlow272 * fRec166[2]) + (fSlow275 * fRec166[1])));
			fRec167[0] = (fTemp14 - ((fSlow272 * fRec167[2]) + (fSlow276 * fRec167[1])));
			fRec168[0] = (fTemp17 - ((fSlow272 * fRec168[2]) + (fSlow277 * fRec168[1])));
			fRec169[0] = (fTemp20 - ((fSlow272 * fRec169[2]) + (fSlow278 * fRec169[1])));
			fRec170[0] = (fTemp23 - ((fSlow272 * fRec170[2]) + (fSlow279 * fRec170[1])));
			fRec171[0] = (fTemp2 - ((fSlow284 * fRec171[2]) + (fSlow283 * fRec171[1])));
			fRec172[0] = (fTemp5 - ((fSlow284 * fRec172[2]) + (fSlow285 * fRec172[1])));
			fRec173[0] = (fTemp8 - ((fSlow284 * fRec173[2]) + (fSlow286 * fRec173[1])));
			fRec174[0] = (fTemp11 - ((fSlow284 * fRec174[2]) + (fSlow287 * fRec174[1])));
			fRec175[0] = (fTemp14 - ((fSlow284 * fRec175[2]) + (fSlow288 * fRec175[1])));
			fRec176[0] = (fTemp17 - ((fSlow284 * fRec176[2]) + (fSlow289 * fRec176[1])));
			fRec177[0] = (fTemp20 - ((fSlow284 * fRec177[2]) + (fSlow290 * fRec177[1])));
			fRec178[0] = (fTemp23 - ((fSlow284 * fRec178[2]) + (fSlow291 * fRec178[1])));
			fRec179[0] = (fTemp2 - ((fSlow296 * fRec179[2]) + (fSlow295 * fRec179[1])));
			fRec180[0] = (fTemp5 - ((fSlow296 * fRec180[2]) + (fSlow297 * fRec180[1])));
			fRec181[0] = (fTemp8 - ((fSlow296 * fRec181[2]) + (fSlow298 * fRec181[1])));
			fRec182[0] = (fTemp11 - ((fSlow296 * fRec182[2]) + (fSlow299 * fRec182[1])));
			fRec183[0] = (fTemp14 - ((fSlow296 * fRec183[2]) + (fSlow300 * fRec183[1])));
			fRec184[0] = (fTemp17 - ((fSlow296 * fRec184[2]) + (fSlow301 * fRec184[1])));
			fRec185[0] = (fTemp20 - ((fSlow296 * fRec185[2]) + (fSlow302 * fRec185[1])));
			fRec186[0] = (fTemp23 - ((fSlow296 * fRec186[2]) + (fSlow303 * fRec186[1])));
			fRec187[0] = (fTemp2 - ((fSlow308 * fRec187[2]) + (fSlow307 * fRec187[1])));
			fRec188[0] = (fTemp5 - ((fSlow308 * fRec188[2]) + (fSlow309 * fRec188[1])));
			fRec189[0] = (fTemp8 - ((fSlow308 * fRec189[2]) + (fSlow310 * fRec189[1])));
			fRec190[0] = (fTemp11 - ((fSlow308 * fRec190[2]) + (fSlow311 * fRec190[1])));
			fRec191[0] = (fTemp14 - ((fSlow308 * fRec191[2]) + (fSlow312 * fRec191[1])));
			fRec192[0] = (fTemp17 - ((fSlow308 * fRec192[2]) + (fSlow313 * fRec192[1])));
			fRec193[0] = (fTemp20 - ((fSlow308 * fRec193[2]) + (fSlow314 * fRec193[1])));
			fRec194[0] = (fTemp23 - ((fSlow308 * fRec194[2]) + (fSlow315 * fRec194[1])));
			fRec195[0] = (fTemp2 - ((fSlow320 * fRec195[2]) + (fSlow319 * fRec195[1])));
			fRec196[0] = (fTemp5 - ((fSlow320 * fRec196[2]) + (fSlow321 * fRec196[1])));
			fRec197[0] = (fTemp8 - ((fSlow320 * fRec197[2]) + (fSlow322 * fRec197[1])));
			fRec198[0] = (fTemp11 - ((fSlow320 * fRec198[2]) + (fSlow323 * fRec198[1])));
			fRec199[0] = (fTemp14 - ((fSlow320 * fRec199[2]) + (fSlow324 * fRec199[1])));
			fRec200[0] = (fTemp17 - ((fSlow320 * fRec200[2]) + (fSlow325 * fRec200[1])));
			fRec201[0] = (fTemp20 - ((fSlow320 * fRec201[2]) + (fSlow326 * fRec201[1])));
			fRec202[0] = (fTemp23 - ((fSlow320 * fRec202[2]) + (fSlow327 * fRec202[1])));
			fRec203[0] = (fTemp2 - ((fSlow332 * fRec203[2]) + (fSlow331 * fRec203[1])));
			fRec204[0] = (fTemp5 - ((fSlow332 * fRec204[2]) + (fSlow333 * fRec204[1])));
			fRec205[0] = (fTemp8 - ((fSlow332 * fRec205[2]) + (fSlow334 * fRec205[1])));
			fRec206[0] = (fTemp11 - ((fSlow332 * fRec206[2]) + (fSlow335 * fRec206[1])));
			fRec207[0] = (fTemp14 - ((fSlow332 * fRec207[2]) + (fSlow336 * fRec207[1])));
			fRec208[0] = (fTemp17 - ((fSlow332 * fRec208[2]) + (fSlow337 * fRec208[1])));
			fRec209[0] = (fTemp20 - ((fSlow332 * fRec209[2]) + (fSlow338 * fRec209[1])));
			fRec210[0] = (fTemp23 - ((fSlow332 * fRec210[2]) + (fSlow339 * fRec210[1])));
			fRec211[0] = (fTemp2 - ((fSlow344 * fRec211[2]) + (fSlow343 * fRec211[1])));
			fRec212[0] = (fTemp5 - ((fSlow344 * fRec212[2]) + (fSlow345 * fRec212[1])));
			fRec213[0] = (fTemp8 - ((fSlow344 * fRec213[2]) + (fSlow346 * fRec213[1])));
			fRec214[0] = (fTemp11 - ((fSlow344 * fRec214[2]) + (fSlow347 * fRec214[1])));
			fRec215[0] = (fTemp14 - ((fSlow344 * fRec215[2]) + (fSlow348 * fRec215[1])));
			fRec216[0] = (fTemp17 - ((fSlow344 * fRec216[2]) + (fSlow349 * fRec216[1])));
			fRec217[0] = (fTemp20 - ((fSlow344 * fRec217[2]) + (fSlow350 * fRec217[1])));
			fRec218[0] = (fTemp23 - ((fSlow344 * fRec218[2]) + (fSlow351 * fRec218[1])));
			fRec219[0] = (fTemp2 - ((fSlow356 * fRec219[2]) + (fSlow355 * fRec219[1])));
			fRec220[0] = (fTemp5 - ((fSlow356 * fRec220[2]) + (fSlow357 * fRec220[1])));
			fRec221[0] = (fTemp8 - ((fSlow356 * fRec221[2]) + (fSlow358 * fRec221[1])));
			fRec222[0] = (fTemp11 - ((fSlow356 * fRec222[2]) + (fSlow359 * fRec222[1])));
			fRec223[0] = (fTemp14 - ((fSlow356 * fRec223[2]) + (fSlow360 * fRec223[1])));
			fRec224[0] = (fTemp17 - ((fSlow356 * fRec224[2]) + (fSlow361 * fRec224[1])));
			fRec225[0] = (fTemp20 - ((fSlow356 * fRec225[2]) + (fSlow362 * fRec225[1])));
			fRec226[0] = (fTemp23 - ((fSlow356 * fRec226[2]) + (fSlow363 * fRec226[1])));
			fRec227[0] = (fTemp2 - ((fSlow368 * fRec227[2]) + (fSlow367 * fRec227[1])));
			fRec228[0] = (fTemp5 - ((fSlow368 * fRec228[2]) + (fSlow369 * fRec228[1])));
			fRec229[0] = (fTemp8 - ((fSlow368 * fRec229[2]) + (fSlow370 * fRec229[1])));
			fRec230[0] = (fTemp11 - ((fSlow368 * fRec230[2]) + (fSlow371 * fRec230[1])));
			fRec231[0] = (fTemp14 - ((fSlow368 * fRec231[2]) + (fSlow372 * fRec231[1])));
			fRec232[0] = (fTemp17 - ((fSlow368 * fRec232[2]) + (fSlow373 * fRec232[1])));
			fRec233[0] = (fTemp20 - ((fSlow368 * fRec233[2]) + (fSlow374 * fRec233[1])));
			fRec234[0] = (fTemp23 - ((fSlow368 * fRec234[2]) + (fSlow375 * fRec234[1])));
			fRec235[0] = (fTemp2 - ((fSlow380 * fRec235[2]) + (fSlow379 * fRec235[1])));
			fRec236[0] = (fTemp5 - ((fSlow380 * fRec236[2]) + (fSlow381 * fRec236[1])));
			fRec237[0] = (fTemp8 - ((fSlow380 * fRec237[2]) + (fSlow382 * fRec237[1])));
			fRec238[0] = (fTemp11 - ((fSlow380 * fRec238[2]) + (fSlow383 * fRec238[1])));
			fRec239[0] = (fTemp14 - ((fSlow380 * fRec239[2]) + (fSlow384 * fRec239[1])));
			fRec240[0] = (fTemp17 - ((fSlow380 * fRec240[2]) + (fSlow385 * fRec240[1])));
			fRec241[0] = (fTemp20 - ((fSlow380 * fRec241[2]) + (fSlow386 * fRec241[1])));
			fRec242[0] = (fTemp23 - ((fSlow380 * fRec242[2]) + (fSlow387 * fRec242[1])));
			fRec243[0] = (fTemp2 - ((fSlow392 * fRec243[2]) + (fSlow391 * fRec243[1])));
			fRec244[0] = (fTemp5 - ((fSlow392 * fRec244[2]) + (fSlow393 * fRec244[1])));
			fRec245[0] = (fTemp8 - ((fSlow392 * fRec245[2]) + (fSlow394 * fRec245[1])));
			fRec246[0] = (fTemp11 - ((fSlow392 * fRec246[2]) + (fSlow395 * fRec246[1])));
			fRec247[0] = (fTemp14 - ((fSlow392 * fRec247[2]) + (fSlow396 * fRec247[1])));
			fRec248[0] = (fTemp17 - ((fSlow392 * fRec248[2]) + (fSlow397 * fRec248[1])));
			fRec249[0] = (fTemp20 - ((fSlow392 * fRec249[2]) + (fSlow398 * fRec249[1])));
			fRec250[0] = (fTemp23 - ((fSlow392 * fRec250[2]) + (fSlow399 * fRec250[1])));
			fRec1[IOTA&32767] = ((0.3f * fRec1[(IOTA-iConst34)&32767]) + (0.033333335f * (((3.7037036e-05f * ((fRec250[0] - fRec250[2]) + ((fRec249[0] - fRec249[2]) + ((fRec248[0] - fRec248[2]) + ((fRec247[0] - fRec247[2]) + ((fRec246[0] - fRec246[2]) + ((fRec245[0] - fRec245[2]) + ((fRec244[0] - fRec244[2]) + (fRec243[0] - fRec243[2]))))))))) + ((0.0002962963f * ((fRec242[0] - fRec242[2]) + ((fRec241[0] - fRec241[2]) + ((fRec240[0] - fRec240[2]) + ((fRec239[0] - fRec239[2]) + ((fRec238[0] - fRec238[2]) + ((fRec237[0] - fRec237[2]) + ((fRec236[0] - fRec236[2]) + (fRec235[0] - fRec235[2]))))))))) + ((0.001f * ((fRec234[0] - fRec234[2]) + ((fRec233[0] - fRec233[2]) + ((fRec232[0] - fRec232[2]) + ((fRec231[0] - fRec231[2]) + ((fRec230[0] - fRec230[2]) + ((fRec229[0] - fRec229[2]) + ((fRec228[0] - fRec228[2]) + (fRec227[0] - fRec227[2]))))))))) + ((0.0023703703f * ((fRec226[0] - fRec226[2]) + ((fRec225[0] - fRec225[2]) + ((fRec224[0] - fRec224[2]) + ((fRec223[0] - fRec223[2]) + ((fRec222[0] - fRec222[2]) + ((fRec221[0] - fRec221[2]) + ((fRec220[0] - fRec220[2]) + (fRec219[0] - fRec219[2]))))))))) + ((0.0046296297f * ((fRec218[0] - fRec218[2]) + ((fRec217[0] - fRec217[2]) + ((fRec216[0] - fRec216[2]) + ((fRec215[0] - fRec215[2]) + ((fRec214[0] - fRec214[2]) + ((fRec213[0] - fRec213[2]) + ((fRec212[0] - fRec212[2]) + (fRec211[0] - fRec211[2]))))))))) + ((0.008f * ((fRec210[0] - fRec210[2]) + ((fRec209[0] - fRec209[2]) + ((fRec208[0] - fRec208[2]) + ((fRec207[0] - fRec207[2]) + ((fRec206[0] - fRec206[2]) + ((fRec205[0] - fRec205[2]) + ((fRec204[0] - fRec204[2]) + (fRec203[0] - fRec203[2]))))))))) + ((0.012703704f * ((fRec202[0] - fRec202[2]) + ((fRec201[0] - fRec201[2]) + ((fRec200[0] - fRec200[2]) + ((fRec199[0] - fRec199[2]) + ((fRec198[0] - fRec198[2]) + ((fRec197[0] - fRec197[2]) + ((fRec196[0] - fRec196[2]) + (fRec195[0] - fRec195[2]))))))))) + ((0.018962963f * ((fRec194[0] - fRec194[2]) + ((fRec193[0] - fRec193[2]) + ((fRec192[0] - fRec192[2]) + ((fRec191[0] - fRec191[2]) + ((fRec190[0] - fRec190[2]) + ((fRec189[0] - fRec189[2]) + ((fRec188[0] - fRec188[2]) + (fRec187[0] - fRec187[2]))))))))) + ((0.027f * ((fRec186[0] - fRec186[2]) + ((fRec185[0] - fRec185[2]) + ((fRec184[0] - fRec184[2]) + ((fRec183[0] - fRec183[2]) + ((fRec182[0] - fRec182[2]) + ((fRec181[0] - fRec181[2]) + ((fRec180[0] - fRec180[2]) + (fRec179[0] - fRec179[2]))))))))) + ((0.037037037f * ((fRec178[0] - fRec178[2]) + ((fRec177[0] - fRec177[2]) + ((fRec176[0] - fRec176[2]) + ((fRec175[0] - fRec175[2]) + ((fRec174[0] - fRec174[2]) + ((fRec173[0] - fRec173[2]) + ((fRec172[0] - fRec172[2]) + (fRec171[0] - fRec171[2]))))))))) + ((0.049296297f * ((fRec170[0] - fRec170[2]) + ((fRec169[0] - fRec169[2]) + ((fRec168[0] - fRec168[2]) + ((fRec167[0] - fRec167[2]) + ((fRec166[0] - fRec166[2]) + ((fRec165[0] - fRec165[2]) + ((fRec164[0] - fRec164[2]) + (fRec163[0] - fRec163[2]))))))))) + ((0.064f * ((fRec162[0] - fRec162[2]) + ((fRec161[0] - fRec161[2]) + ((fRec160[0] - fRec160[2]) + ((fRec159[0] - fRec159[2]) + ((fRec158[0] - fRec158[2]) + ((fRec157[0] - fRec157[2]) + ((fRec156[0] - fRec156[2]) + (fRec155[0] - fRec155[2]))))))))) + ((0.08137037f * ((fRec154[0] - fRec154[2]) + ((fRec153[0] - fRec153[2]) + ((fRec152[0] - fRec152[2]) + ((fRec151[0] - fRec151[2]) + ((fRec150[0] - fRec150[2]) + ((fRec149[0] - fRec149[2]) + ((fRec148[0] - fRec148[2]) + (fRec147[0] - fRec147[2]))))))))) + ((0.10162963f * ((fRec146[0] - fRec146[2]) + ((fRec145[0] - fRec145[2]) + ((fRec144[0] - fRec144[2]) + ((fRec143[0] - fRec143[2]) + ((fRec142[0] - fRec142[2]) + ((fRec141[0] - fRec141[2]) + ((fRec140[0] - fRec140[2]) + (fRec139[0] - fRec139[2]))))))))) + ((0.125f * ((fRec138[0] - fRec138[2]) + ((fRec137[0] - fRec137[2]) + ((fRec136[0] - fRec136[2]) + ((fRec135[0] - fRec135[2]) + ((fRec134[0] - fRec134[2]) + ((fRec133[0] - fRec133[2]) + ((fRec132[0] - fRec132[2]) + (fRec131[0] - fRec131[2]))))))))) + ((0.1517037f * ((fRec130[0] - fRec130[2]) + ((fRec129[0] - fRec129[2]) + ((fRec128[0] - fRec128[2]) + ((fRec127[0] - fRec127[2]) + ((fRec126[0] - fRec126[2]) + ((fRec125[0] - fRec125[2]) + ((fRec124[0] - fRec124[2]) + (fRec123[0] - fRec123[2]))))))))) + ((0.18196297f * ((fRec122[0] - fRec122[2]) + ((fRec121[0] - fRec121[2]) + ((fRec120[0] - fRec120[2]) + ((fRec119[0] - fRec119[2]) + ((fRec118[0] - fRec118[2]) + ((fRec117[0] - fRec117[2]) + ((fRec116[0] - fRec116[2]) + (fRec115[0] - fRec115[2]))))))))) + ((0.216f * ((fRec114[0] - fRec114[2]) + ((fRec113[0] - fRec113[2]) + ((fRec112[0] - fRec112[2]) + ((fRec111[0] - fRec111[2]) + ((fRec110[0] - fRec110[2]) + ((fRec109[0] - fRec109[2]) + ((fRec108[0] - fRec108[2]) + (fRec107[0] - fRec107[2]))))))))) + ((0.25403702f * ((fRec106[0] - fRec106[2]) + ((fRec105[0] - fRec105[2]) + ((fRec104[0] - fRec104[2]) + ((fRec103[0] - fRec103[2]) + ((fRec102[0] - fRec102[2]) + ((fRec101[0] - fRec101[2]) + ((fRec100[0] - fRec100[2]) + (fRec99[0] - fRec99[2]))))))))) + ((0.2962963f * ((fRec98[0] - fRec98[2]) + ((fRec97[0] - fRec97[2]) + ((fRec96[0] - fRec96[2]) + ((fRec95[0] - fRec95[2]) + ((fRec94[0] - fRec94[2]) + ((fRec93[0] - fRec93[2]) + ((fRec92[0] - fRec92[2]) + (fRec91[0] - fRec91[2]))))))))) + ((0.343f * ((fRec90[0] - fRec90[2]) + ((fRec89[0] - fRec89[2]) + ((fRec88[0] - fRec88[2]) + ((fRec87[0] - fRec87[2]) + ((fRec86[0] - fRec86[2]) + ((fRec85[0] - fRec85[2]) + ((fRec84[0] - fRec84[2]) + (fRec83[0] - fRec83[2]))))))))) + ((0.39437038f * ((fRec82[0] - fRec82[2]) + ((fRec81[0] - fRec81[2]) + ((fRec80[0] - fRec80[2]) + ((fRec79[0] - fRec79[2]) + ((fRec78[0] - fRec78[2]) + ((fRec77[0] - fRec77[2]) + ((fRec76[0] - fRec76[2]) + (fRec75[0] - fRec75[2]))))))))) + ((0.45062962f * ((fRec74[0] - fRec74[2]) + ((fRec73[0] - fRec73[2]) + ((fRec72[0] - fRec72[2]) + ((fRec71[0] - fRec71[2]) + ((fRec70[0] - fRec70[2]) + ((fRec69[0] - fRec69[2]) + ((fRec68[0] - fRec68[2]) + (fRec67[0] - fRec67[2]))))))))) + ((0.512f * ((fRec66[0] - fRec66[2]) + ((fRec65[0] - fRec65[2]) + ((fRec64[0] - fRec64[2]) + ((fRec63[0] - fRec63[2]) + ((fRec62[0] - fRec62[2]) + ((fRec61[0] - fRec61[2]) + ((fRec60[0] - fRec60[2]) + (fRec59[0] - fRec59[2]))))))))) + ((0.5787037f * ((fRec58[0] - fRec58[2]) + ((fRec57[0] - fRec57[2]) + ((fRec56[0] - fRec56[2]) + ((fRec55[0] - fRec55[2]) + ((fRec54[0] - fRec54[2]) + ((fRec53[0] - fRec53[2]) + ((fRec52[0] - fRec52[2]) + (fRec51[0] - fRec51[2]))))))))) + ((0.65096295f * ((fRec50[0] - fRec50[2]) + ((fRec49[0] - fRec49[2]) + ((fRec48[0] - fRec48[2]) + ((fRec47[0] - fRec47[2]) + ((fRec46[0] - fRec46[2]) + ((fRec45[0] - fRec45[2]) + ((fRec44[0] - fRec44[2]) + (fRec43[0] - fRec43[2]))))))))) + ((0.729f * ((fRec42[0] - fRec42[2]) + ((fRec41[0] - fRec41[2]) + ((fRec40[0] - fRec40[2]) + ((fRec39[0] - fRec39[2]) + ((fRec38[0] - fRec38[2]) + ((fRec37[0] - fRec37[2]) + ((fRec36[0] - fRec36[2]) + (fRec35[0] - fRec35[2]))))))))) + ((0.81303704f * ((fRec34[0] - fRec34[2]) + ((fRec33[0] - fRec33[2]) + ((fRec32[0] - fRec32[2]) + ((fRec31[0] - fRec31[2]) + ((fRec30[0] - fRec30[2]) + ((fRec29[0] - fRec29[2]) + ((fRec28[0] - fRec28[2]) + (fRec27[0] - fRec27[2]))))))))) + ((0.9032963f * ((fRec26[0] - fRec26[2]) + ((fRec25[0] - fRec25[2]) + ((fRec24[0] - fRec24[2]) + ((fRec23[0] - fRec23[2]) + ((fRec22[0] - fRec22[2]) + ((fRec21[0] - fRec21[2]) + ((fRec20[0] - fRec20[2]) + (fRec19[0] - fRec19[2]))))))))) + (fRec17[0] + (fRec15[0] + (fRec13[0] + (fRec11[0] + (fRec9[0] + (fRec7[0] + (fRec5[0] + fRec2[0])))))))))))))))))))))))))))))))))))) - (fRec17[2] + (fRec15[2] + (fRec13[2] + (fRec11[2] + (fRec9[2] + (fRec7[2] + (fRec5[2] + fRec2[2]))))))))));
			fRec0[IOTA&131071] = ((fSlow402 * fRec0[(IOTA-iSlow401)&131071]) + (fSlow400 * fRec1[(IOTA-0)&32767]));
			float fTemp24 = fRec0[(IOTA-0)&131071];
			output0[i] = (FAUSTFLOAT)fTemp24;
			output1[i] = (FAUSTFLOAT)fTemp24;
			// post processing
			IOTA = IOTA+1;
			fRec250[2] = fRec250[1]; fRec250[1] = fRec250[0];
			fRec249[2] = fRec249[1]; fRec249[1] = fRec249[0];
			fRec248[2] = fRec248[1]; fRec248[1] = fRec248[0];
			fRec247[2] = fRec247[1]; fRec247[1] = fRec247[0];
			fRec246[2] = fRec246[1]; fRec246[1] = fRec246[0];
			fRec245[2] = fRec245[1]; fRec245[1] = fRec245[0];
			fRec244[2] = fRec244[1]; fRec244[1] = fRec244[0];
			fRec243[2] = fRec243[1]; fRec243[1] = fRec243[0];
			fRec242[2] = fRec242[1]; fRec242[1] = fRec242[0];
			fRec241[2] = fRec241[1]; fRec241[1] = fRec241[0];
			fRec240[2] = fRec240[1]; fRec240[1] = fRec240[0];
			fRec239[2] = fRec239[1]; fRec239[1] = fRec239[0];
			fRec238[2] = fRec238[1]; fRec238[1] = fRec238[0];
			fRec237[2] = fRec237[1]; fRec237[1] = fRec237[0];
			fRec236[2] = fRec236[1]; fRec236[1] = fRec236[0];
			fRec235[2] = fRec235[1]; fRec235[1] = fRec235[0];
			fRec234[2] = fRec234[1]; fRec234[1] = fRec234[0];
			fRec233[2] = fRec233[1]; fRec233[1] = fRec233[0];
			fRec232[2] = fRec232[1]; fRec232[1] = fRec232[0];
			fRec231[2] = fRec231[1]; fRec231[1] = fRec231[0];
			fRec230[2] = fRec230[1]; fRec230[1] = fRec230[0];
			fRec229[2] = fRec229[1]; fRec229[1] = fRec229[0];
			fRec228[2] = fRec228[1]; fRec228[1] = fRec228[0];
			fRec227[2] = fRec227[1]; fRec227[1] = fRec227[0];
			fRec226[2] = fRec226[1]; fRec226[1] = fRec226[0];
			fRec225[2] = fRec225[1]; fRec225[1] = fRec225[0];
			fRec224[2] = fRec224[1]; fRec224[1] = fRec224[0];
			fRec223[2] = fRec223[1]; fRec223[1] = fRec223[0];
			fRec222[2] = fRec222[1]; fRec222[1] = fRec222[0];
			fRec221[2] = fRec221[1]; fRec221[1] = fRec221[0];
			fRec220[2] = fRec220[1]; fRec220[1] = fRec220[0];
			fRec219[2] = fRec219[1]; fRec219[1] = fRec219[0];
			fRec218[2] = fRec218[1]; fRec218[1] = fRec218[0];
			fRec217[2] = fRec217[1]; fRec217[1] = fRec217[0];
			fRec216[2] = fRec216[1]; fRec216[1] = fRec216[0];
			fRec215[2] = fRec215[1]; fRec215[1] = fRec215[0];
			fRec214[2] = fRec214[1]; fRec214[1] = fRec214[0];
			fRec213[2] = fRec213[1]; fRec213[1] = fRec213[0];
			fRec212[2] = fRec212[1]; fRec212[1] = fRec212[0];
			fRec211[2] = fRec211[1]; fRec211[1] = fRec211[0];
			fRec210[2] = fRec210[1]; fRec210[1] = fRec210[0];
			fRec209[2] = fRec209[1]; fRec209[1] = fRec209[0];
			fRec208[2] = fRec208[1]; fRec208[1] = fRec208[0];
			fRec207[2] = fRec207[1]; fRec207[1] = fRec207[0];
			fRec206[2] = fRec206[1]; fRec206[1] = fRec206[0];
			fRec205[2] = fRec205[1]; fRec205[1] = fRec205[0];
			fRec204[2] = fRec204[1]; fRec204[1] = fRec204[0];
			fRec203[2] = fRec203[1]; fRec203[1] = fRec203[0];
			fRec202[2] = fRec202[1]; fRec202[1] = fRec202[0];
			fRec201[2] = fRec201[1]; fRec201[1] = fRec201[0];
			fRec200[2] = fRec200[1]; fRec200[1] = fRec200[0];
			fRec199[2] = fRec199[1]; fRec199[1] = fRec199[0];
			fRec198[2] = fRec198[1]; fRec198[1] = fRec198[0];
			fRec197[2] = fRec197[1]; fRec197[1] = fRec197[0];
			fRec196[2] = fRec196[1]; fRec196[1] = fRec196[0];
			fRec195[2] = fRec195[1]; fRec195[1] = fRec195[0];
			fRec194[2] = fRec194[1]; fRec194[1] = fRec194[0];
			fRec193[2] = fRec193[1]; fRec193[1] = fRec193[0];
			fRec192[2] = fRec192[1]; fRec192[1] = fRec192[0];
			fRec191[2] = fRec191[1]; fRec191[1] = fRec191[0];
			fRec190[2] = fRec190[1]; fRec190[1] = fRec190[0];
			fRec189[2] = fRec189[1]; fRec189[1] = fRec189[0];
			fRec188[2] = fRec188[1]; fRec188[1] = fRec188[0];
			fRec187[2] = fRec187[1]; fRec187[1] = fRec187[0];
			fRec186[2] = fRec186[1]; fRec186[1] = fRec186[0];
			fRec185[2] = fRec185[1]; fRec185[1] = fRec185[0];
			fRec184[2] = fRec184[1]; fRec184[1] = fRec184[0];
			fRec183[2] = fRec183[1]; fRec183[1] = fRec183[0];
			fRec182[2] = fRec182[1]; fRec182[1] = fRec182[0];
			fRec181[2] = fRec181[1]; fRec181[1] = fRec181[0];
			fRec180[2] = fRec180[1]; fRec180[1] = fRec180[0];
			fRec179[2] = fRec179[1]; fRec179[1] = fRec179[0];
			fRec178[2] = fRec178[1]; fRec178[1] = fRec178[0];
			fRec177[2] = fRec177[1]; fRec177[1] = fRec177[0];
			fRec176[2] = fRec176[1]; fRec176[1] = fRec176[0];
			fRec175[2] = fRec175[1]; fRec175[1] = fRec175[0];
			fRec174[2] = fRec174[1]; fRec174[1] = fRec174[0];
			fRec173[2] = fRec173[1]; fRec173[1] = fRec173[0];
			fRec172[2] = fRec172[1]; fRec172[1] = fRec172[0];
			fRec171[2] = fRec171[1]; fRec171[1] = fRec171[0];
			fRec170[2] = fRec170[1]; fRec170[1] = fRec170[0];
			fRec169[2] = fRec169[1]; fRec169[1] = fRec169[0];
			fRec168[2] = fRec168[1]; fRec168[1] = fRec168[0];
			fRec167[2] = fRec167[1]; fRec167[1] = fRec167[0];
			fRec166[2] = fRec166[1]; fRec166[1] = fRec166[0];
			fRec165[2] = fRec165[1]; fRec165[1] = fRec165[0];
			fRec164[2] = fRec164[1]; fRec164[1] = fRec164[0];
			fRec163[2] = fRec163[1]; fRec163[1] = fRec163[0];
			fRec162[2] = fRec162[1]; fRec162[1] = fRec162[0];
			fRec161[2] = fRec161[1]; fRec161[1] = fRec161[0];
			fRec160[2] = fRec160[1]; fRec160[1] = fRec160[0];
			fRec159[2] = fRec159[1]; fRec159[1] = fRec159[0];
			fRec158[2] = fRec158[1]; fRec158[1] = fRec158[0];
			fRec157[2] = fRec157[1]; fRec157[1] = fRec157[0];
			fRec156[2] = fRec156[1]; fRec156[1] = fRec156[0];
			fRec155[2] = fRec155[1]; fRec155[1] = fRec155[0];
			fRec154[2] = fRec154[1]; fRec154[1] = fRec154[0];
			fRec153[2] = fRec153[1]; fRec153[1] = fRec153[0];
			fRec152[2] = fRec152[1]; fRec152[1] = fRec152[0];
			fRec151[2] = fRec151[1]; fRec151[1] = fRec151[0];
			fRec150[2] = fRec150[1]; fRec150[1] = fRec150[0];
			fRec149[2] = fRec149[1]; fRec149[1] = fRec149[0];
			fRec148[2] = fRec148[1]; fRec148[1] = fRec148[0];
			fRec147[2] = fRec147[1]; fRec147[1] = fRec147[0];
			fRec146[2] = fRec146[1]; fRec146[1] = fRec146[0];
			fRec145[2] = fRec145[1]; fRec145[1] = fRec145[0];
			fRec144[2] = fRec144[1]; fRec144[1] = fRec144[0];
			fRec143[2] = fRec143[1]; fRec143[1] = fRec143[0];
			fRec142[2] = fRec142[1]; fRec142[1] = fRec142[0];
			fRec141[2] = fRec141[1]; fRec141[1] = fRec141[0];
			fRec140[2] = fRec140[1]; fRec140[1] = fRec140[0];
			fRec139[2] = fRec139[1]; fRec139[1] = fRec139[0];
			fRec138[2] = fRec138[1]; fRec138[1] = fRec138[0];
			fRec137[2] = fRec137[1]; fRec137[1] = fRec137[0];
			fRec136[2] = fRec136[1]; fRec136[1] = fRec136[0];
			fRec135[2] = fRec135[1]; fRec135[1] = fRec135[0];
			fRec134[2] = fRec134[1]; fRec134[1] = fRec134[0];
			fRec133[2] = fRec133[1]; fRec133[1] = fRec133[0];
			fRec132[2] = fRec132[1]; fRec132[1] = fRec132[0];
			fRec131[2] = fRec131[1]; fRec131[1] = fRec131[0];
			fRec130[2] = fRec130[1]; fRec130[1] = fRec130[0];
			fRec129[2] = fRec129[1]; fRec129[1] = fRec129[0];
			fRec128[2] = fRec128[1]; fRec128[1] = fRec128[0];
			fRec127[2] = fRec127[1]; fRec127[1] = fRec127[0];
			fRec126[2] = fRec126[1]; fRec126[1] = fRec126[0];
			fRec125[2] = fRec125[1]; fRec125[1] = fRec125[0];
			fRec124[2] = fRec124[1]; fRec124[1] = fRec124[0];
			fRec123[2] = fRec123[1]; fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1]; fRec122[1] = fRec122[0];
			fRec121[2] = fRec121[1]; fRec121[1] = fRec121[0];
			fRec120[2] = fRec120[1]; fRec120[1] = fRec120[0];
			fRec119[2] = fRec119[1]; fRec119[1] = fRec119[0];
			fRec118[2] = fRec118[1]; fRec118[1] = fRec118[0];
			fRec117[2] = fRec117[1]; fRec117[1] = fRec117[0];
			fRec116[2] = fRec116[1]; fRec116[1] = fRec116[0];
			fRec115[2] = fRec115[1]; fRec115[1] = fRec115[0];
			fRec114[2] = fRec114[1]; fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1]; fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1]; fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1]; fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1]; fRec110[1] = fRec110[0];
			fRec109[2] = fRec109[1]; fRec109[1] = fRec109[0];
			fRec108[2] = fRec108[1]; fRec108[1] = fRec108[0];
			fRec107[2] = fRec107[1]; fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1]; fRec106[1] = fRec106[0];
			fRec105[2] = fRec105[1]; fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1]; fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1]; fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1]; fRec102[1] = fRec102[0];
			fRec101[2] = fRec101[1]; fRec101[1] = fRec101[0];
			fRec100[2] = fRec100[1]; fRec100[1] = fRec100[0];
			fRec99[2] = fRec99[1]; fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1]; fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1]; fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1]; fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1]; fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1]; fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1]; fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1]; fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1]; fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1]; fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1]; fRec89[1] = fRec89[0];
			fRec88[2] = fRec88[1]; fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1]; fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1]; fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1]; fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1]; fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1]; fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1]; fRec82[1] = fRec82[0];
			fRec81[2] = fRec81[1]; fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1]; fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1]; fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1]; fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1]; fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1]; fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1]; fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1]; fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1]; fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1]; fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1]; fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1]; fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1]; fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1]; fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1]; fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1]; fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1]; fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1]; fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1]; fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1]; fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1]; fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1]; fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1]; fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1]; fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1]; fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1]; fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1]; fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1]; fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1]; fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1]; fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1]; fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1]; fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1]; fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1]; fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1]; fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
			fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			iVec15[1] = iVec15[0];
			fVec14[1] = fVec14[0];
			fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			iVec13[1] = iVec13[0];
			fVec12[1] = fVec12[0];
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			iVec11[1] = iVec11[0];
			fVec10[1] = fVec10[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			iVec9[1] = iVec9[0];
			fVec8[1] = fVec8[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			iVec7[1] = iVec7[0];
			fVec6[1] = fVec6[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			iVec5[1] = iVec5[0];
			fVec4[1] = fVec4[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			iVec3[1] = iVec3[0];
			fVec2[1] = fVec2[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			iRec4[1] = iRec4[0];
			fRec3[1] = fRec3[0];
			iVec1[1] = iVec1[0];
			fVec0[1] = fVec0[0];
		}
	}
};



/*
 * README:
 * The file only implements the native part of faust2android applications.
 * The native C API is documented at the end of this file in the "Native Faust
 * API" section.
 */

//**************************************************************
// Polyphony
//**************************************************************

/************************************************************************
	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef __dsp_combiner__
#define __dsp_combiner__

#include <string.h>
#include <assert.h>

// Combine two DSP in sequence

class dsp_sequencer : public dsp {
    
    private:
        
        dsp* fDSP1;
        dsp* fDSP2;
        FAUSTFLOAT** fSeqBuffer;
         
    public:
        
        dsp_sequencer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096)
            :fDSP1(dsp1), fDSP2(dsp2)
        {
            assert(fDSP1->getNumOutputs() == fDSP2->getNumInputs());
            fSeqBuffer = new FAUSTFLOAT*[fDSP1->getNumOutputs()];
            for (int i = 0; i < fDSP1->getNumOutputs(); i++) {
                fSeqBuffer[i] = new FAUSTFLOAT[buffer_size];
            }
        }
        
        virtual ~dsp_sequencer()
        {
            for (int i = 0; i < fDSP1->getNumOutputs(); i++) {
               delete [] fSeqBuffer[i];
            }
            
            delete [] fSeqBuffer;
            delete fDSP1;
            delete fDSP2;
        }
               
        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }
    
        virtual void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openTabBox("DSP sequencer");
            ui_interface->openVerticalBox("DSP1");
            fDSP1->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->openVerticalBox("DSP2");
            fDSP2->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->closeBox();
        }
        
        virtual int getSampleRate()
        {
            return fDSP1->getSampleRate();
        }
    
        virtual void init(int samplingRate)
        {
            fDSP1->init(samplingRate);
            fDSP2->init(samplingRate);
        }
    
        virtual void instanceInit(int samplingRate)
        {
            fDSP1->instanceInit(samplingRate);
            fDSP2->instanceInit(samplingRate);
        }
    
        virtual void instanceConstants(int samplingRate)
        {
            fDSP1->instanceConstants(samplingRate);
            fDSP2->instanceConstants(samplingRate);
        }
    
        virtual void instanceResetUserInterface()
        {
            fDSP1->instanceResetUserInterface();
            fDSP2->instanceResetUserInterface();
        }
    
        virtual void instanceClear()
        {
            fDSP1->instanceClear();
            fDSP2->instanceClear();
        }
        
        virtual dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone());
        }
    
        virtual void metadata(Meta* m)
        {
            fDSP1->metadata(m);
            fDSP2->metadata(m);
        }
 
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fSeqBuffer);
            fDSP2->compute(count, fSeqBuffer, outputs);
        }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Combine two DSP in parallel

class dsp_parallelizer : public dsp {
    
    private:
        
        dsp* fDSP1;
        dsp* fDSP2;
         
    public:
        
        dsp_parallelizer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096)
            :fDSP1(dsp1), fDSP2(dsp2)
        {}
        
        virtual ~dsp_parallelizer()
        {
            delete fDSP1;
            delete fDSP2;
        }
               
        virtual int getNumInputs() { return fDSP1->getNumInputs() + fDSP2->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs() + fDSP2->getNumOutputs(); }
    
        virtual void buildUserInterface(UI* ui_interface)
        {
            ui_interface->openTabBox("DSP parallelizer");
            ui_interface->openVerticalBox("DSP1");
            fDSP1->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->openVerticalBox("DSP2");
            fDSP2->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->closeBox();
        }
        
        virtual int getSampleRate()
        {
            return fDSP1->getSampleRate();
        }
    
        virtual void init(int samplingRate)
        {
            fDSP1->init(samplingRate);
            fDSP2->init(samplingRate);
        }
    
        virtual void instanceInit(int samplingRate)
        {
            fDSP1->instanceInit(samplingRate);
            fDSP2->instanceInit(samplingRate);
        }
    
        virtual void instanceConstants(int samplingRate)
        {
            fDSP1->instanceConstants(samplingRate);
            fDSP2->instanceConstants(samplingRate);
        }
        
        virtual void instanceResetUserInterface()
        {
            fDSP1->instanceResetUserInterface();
            fDSP2->instanceResetUserInterface();
        }
    
        virtual void instanceClear()
        {
            fDSP1->instanceClear();
            fDSP2->instanceClear();
        }
        
        virtual dsp* clone()
        {
            return new dsp_parallelizer(fDSP1->clone(), fDSP2->clone());
        }

        virtual void metadata(Meta* m)
        {
            fDSP1->metadata(m);
            fDSP2->metadata(m);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, outputs);
            
            // Shift inputs/outputs channels for fDSP2
            FAUSTFLOAT** inputs_dsp2 = (FAUSTFLOAT**)alloca(fDSP2->getNumInputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                inputs_dsp2[chan] = inputs[fDSP1->getNumInputs() + chan];
            }
            
            FAUSTFLOAT** outputs_dsp2 = (FAUSTFLOAT**)alloca(fDSP2->getNumOutputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                outputs_dsp2[chan] = inputs[fDSP1->getNumOutputs() + chan];
            }
            
            fDSP2->compute(count, inputs_dsp2, outputs_dsp2);
        }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

#endif
/************************************************************************
 ************************************************************************
 FAUST Polyphonic Architecture File
 Copyright (C) 2013 GRAME, Romain Michon, CCRMA - Stanford University
 Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------

 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#ifndef __faust_poly_engine__
#define __faust_poly_engine__

#include <math.h>
#include <stdio.h>
#include <string.h>

/************************************************************************
	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

						An abstraction layer over audio layer

*******************************************************************************
*******************************************************************************/

#ifndef __audio__
#define __audio__
			
class dsp;

typedef void (* shutdown_callback)(const char* message, void* arg);

class audio {
    
 public:
			 audio() {}
	virtual ~audio() {}
	
	virtual bool init(const char* name, dsp*)               = 0;
	virtual bool start()                                    = 0;
	virtual void stop()                                     = 0;
    virtual void shutdown(shutdown_callback cb, void* arg)  {}
    
    virtual int get_buffer_size() = 0;
    virtual int get_sample_rate() = 0;
    
    virtual int get_num_inputs() { return -1; }
    virtual int get_num_outputs() { return -1; }
    
    virtual float get_cpu_load() { return 0.f; }
};
					
#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>

/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

class JSONUI : public PathBuilder, public Meta, public UI
{

    protected:
    
        std::stringstream fJSON;
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fName;
        std::string fExpandedCode;
        std::string fSHAKey;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
        
        void init(const std::string& name, int inputs, int outputs, const std::string& sha_key, const std::string& dsp_code)
        {
            fTab = 1;
            
            // Start Meta generation
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fInputs = inputs;
            fOutputs = outputs;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
        }
        
        inline std::string flatten(const std::string& src)
        {
            std::stringstream dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        dst << ' ';
                        break;
                    case '"':
                        dst << "\\" << '"';
                        break;
                    default:
                        dst << src[i];
                        break;
                }
            }
            return dst.str();
        }
      
     public:
     
        JSONUI(const std::string& name, int inputs, int outputs, const std::string& sha_key, const std::string& dsp_code)
        {
            init(name, inputs, outputs, sha_key, dsp_code);
        }

        JSONUI(const std::string& name, int inputs, int outputs)
        {
            init(name, inputs, outputs, "", "");
        }

        JSONUI(int inputs, int outputs)
        {
            init("", inputs, outputs, "", "");
        }
        
        JSONUI()
        {
            init("", -1, -1, "", "");
        }
 
        virtual ~JSONUI() {}

        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            fControlsLevel.push_back(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab + 1);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            fControlsLevel.pop_back();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
    
        virtual void addGenericButton(const char* label, const char* name)
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            addMeta(fTab + 1, false);
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ",";
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"init\": \"" << init << "\",";
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\",";
            tab(fTab + 1, fUI); fUI << "\"step\": \"" << step << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab + 1, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab + 1, fUI); fUI << "\"address\": \"" << buildPath(label) << "\"" << ",";
            addMeta(fTab + 1);
            tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
            tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\"";
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            fJSON << "{";
            fTab += 1;
            tab(fTab, fJSON); fJSON << "\"name\": \"" << fName << "\",";
            if (fSHAKey != "") { tab(fTab, fJSON); fJSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, fJSON); fJSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, fJSON); fJSON << "\"inputs\": \"" << fInputs << "\","; 
            tab(fTab, fJSON); fJSON << "\"outputs\": \"" << fOutputs << "\",";
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                fJSON << fMeta.str() << fUI.str();
            } else {
                fJSON << fUI.str();
            }
            tab(fTab, fJSON); fJSON << "}" << std::endl;
            return (flat) ? flatten(fJSON.str()) : fJSON.str();
        }
    
};

#endif // FAUST_JSONUI_H
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef API_UI_H
#define API_UI_H

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
								ValueConverter.h
							    (GRAME, © 2015)

Set of conversion objects used to map user interface values (for example a gui slider
delivering values between 0 and 1) to faust values (for example a vslider between
20 and 20000) using a log scale.

-- Utilities

Range(lo,hi) : clip a value x between lo and hi
Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2

-- Value Converters

ValueConverter::ui2faust(x)
ValueConverter::faust2ui(x)

-- ValueConverters used for sliders depending of the scale

LinearValueConverter(umin, umax, fmin, fmax)
LogValueConverter(umin, umax, fmin, fmax)
ExpValueConverter(umin, umax, fmin, fmax)

-- ValueConverters used for accelerometers based on 3 points

AccUpConverter(amin, amid, amax, fmin, fmid, fmax)		-- curve 0
AccDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 1
AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 2
AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 3

-- lists of ZoneControl are used to implement accelerometers metadata for each axes

ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter

-- ZoneReader are used to implement screencolor metadata

ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef   		with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef				with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min(x,y)), fHi(std::max(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) = 0;
        virtual double faust2ui(double x) = 0;
};

//--------------------------------------------------------------------------------------
// Linear conversion between ui and faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{

    private:

        Interpolator fUI2F;
        Interpolator fF2UI;

    public:

        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}

        LinearValueConverter() :
            fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) {	return fUI2F(x); }
        virtual double faust2ui(double x) {	return fF2UI(x); }

};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, log(std::max(DBL_MIN,fmin)), log(std::max(DBL_MIN,fmax)))
        {}

        virtual double ui2faust(double x) 	{ return exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x)	{ return LinearValueConverter::faust2ui(log(std::max(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, exp(fmin), exp(fmax))
        {}

        virtual double ui2faust(double x) { return log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(exp(x)); }

};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {

    protected:

        bool fActive;

    public:

        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}

        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;

        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmin,fmid,fmax);
            fF2A = Interpolator3pt(fmin,fmid,fmax,amin,amid,amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmax,fmid,fmin);
            fF2A = Interpolator3pt(fmin,fmid,fmax,amax,amid,amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotone function
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmin,fmax,fmin);
            fF2A = Interpolator(fmin,fmax,amin,amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotone function
        {}

        virtual double ui2faust(double x)	{ return fA2F(x); }
        virtual double faust2ui(double x)	{ return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin,amid,amax,fmax,fmin,fmax);
            fF2A = Interpolator(fmin,fmax,amin,amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    private:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* valueConverter) : ZoneControl(zone), fValueConverter(valueConverter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        void update(double v) { *fZone = fValueConverter->ui2faust(v); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                delete(*it);
            }
        }
        void update(double v) { if (fValueConverters[fCurve]->getActive()) *fZone = fValueConverters[fCurve]->ui2faust(v); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                (*it)->setActive(on_off);
            }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT*     fZone;
        Interpolator    fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue() {
            if (fZone != 0) {
                return (int)fInterpolator(*fZone);
            } else {
                return 127;
            }
        }

};

#endif
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

enum { kLin = 0, kLog = 1, kExp = 2 };

class APIUI : public PathBuilder, public Meta, public UI
{
    protected:

        int	fNumParameters;
        std::vector<std::string>        fName;
        std::map<std::string, int>      fMap;
        std::vector<ValueConverter*>    fConversion;
        std::vector<FAUSTFLOAT*>        fZone;
        std::vector<FAUSTFLOAT>         fInit;
        std::vector<FAUSTFLOAT>         fMin;
        std::vector<FAUSTFLOAT>         fMax;
        std::vector<FAUSTFLOAT>         fStep;
        std::vector<std::string>	fUnit;
        std::vector<ZoneControl*>	fAcc[3];
        std::vector<ZoneControl*>	fGyr[3];

        // Screen color control
        // "...[screencolor:red]..." etc.
        bool fHasScreenControl;      // true if control screen color metadata
        ZoneReader* fRedReader;
        ZoneReader* fGreenReader;
        ZoneReader* fBlueReader;

        // Current values controlled by metadata
        std::string fCurrentUnit;
        int fCurrentScale;
        std::string fCurrentAcc;
        std::string fCurrentGyr;
        std::string fCurrentColor;

        // Add a generic parameter
        virtual void addParameter(const char* label,
                                FAUSTFLOAT* zone,
                                FAUSTFLOAT init,
                                FAUSTFLOAT min,
                                FAUSTFLOAT max,
                                FAUSTFLOAT step)
        {
            std::string name = buildPath(label);

            fMap[name] = fNumParameters++;
            fName.push_back(name);
            fZone.push_back(zone);
            fInit.push_back(init);
            fMin.push_back(min);
            fMax.push_back(max);
            fStep.push_back(step);

            //handle unit metadata
            fUnit.push_back(fCurrentUnit);
            fCurrentUnit = "";

            //handle scale metadata
            switch (fCurrentScale) {
                case kLin : fConversion.push_back(new LinearValueConverter(0,1, min, max)); break;
                case kLog : fConversion.push_back(new LogValueConverter(0,1, min, max)); break;
                case kExp : fConversion.push_back(new ExpValueConverter(0,1, min, max)); break;
            }
            fCurrentScale = kLin;

            // handle acc metadata "...[acc : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentAcc.size() > 0) {
                std::istringstream iss(fCurrentAcc);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fAcc[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    std::cerr << "incorrect acc metadata : " << fCurrentAcc << std::endl;
                }
            }
            fCurrentAcc = "";

            // handle gyr metadata "...[gyr : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentGyr.size() > 0) {
                std::istringstream iss(fCurrentGyr);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fGyr[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    std::cerr << "incorrect gyr metadata : " << fCurrentGyr << std::endl;
                }
            }
            fCurrentGyr = "";

            // handle screencolor metadata "...[screencolor:red|green|blue]..."
            if (fCurrentColor.size() > 0) {
                if ((fCurrentColor == "red") && (fRedReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "green") && (fGreenReader == 0)) {
                    fGreenReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "blue") && (fBlueReader == 0)) {
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "white") && (fRedReader == 0) && (fGreenReader == 0) && (fBlueReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fGreenReader = new ZoneReader(zone, min, max);
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else {
                    std::cerr << "incorrect screencolor metadata : " << fCurrentColor << std::endl;
                }
            }
            fCurrentColor = "";
        }

        int getZoneIndex(std::vector<ZoneControl*>* table, int p, int val)
        {
            FAUSTFLOAT* zone = fZone[p];
            for (int i = 0; i < table[val].size(); i++) {
                if (zone == table[val][i]->getZone()) return i;
            }
            return -1;
        }
    
        void setConverter(std::vector<ZoneControl*>* table, int p, int val, int curve, double amin, double amid, double amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            // Deactivates everywhere..
            if (id1 != -1) table[0][id1]->setActive(false);
            if (id2 != -1) table[1][id2]->setActive(false);
            if (id3 != -1) table[2][id3]->setActive(false);
            
            if (val == -1) { // Means: no more mapping...
                // So stay all deactivated...
            } else {
                int id4 = getZoneIndex(table, p, val);
                if (id4 != -1) {
                    // Reactivate the one we edit...
                    table[val][id4]->setMappingValues(curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]);
                    table[val][id4]->setActive(true);
                } else {
                    // Allocate a new CurveZoneControl which is 'active' by default
                    FAUSTFLOAT* zone = fZone[p];
                    table[val].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]));
                }
            }
        }
    
        void getConverter(std::vector<ZoneControl*>* table, int p, int& val, int& curve, double& amin, double& amid, double& amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            if (id1 != -1) {
                val = 0;
                curve = fAcc[val][id1]->getCurve();
                table[val][id1]->getMappingValues(amin, amid, amax);
            } else if (id2 != -1) {
                val = 1;
                curve = fAcc[val][id2]->getCurve();
                table[val][id2]->getMappingValues(amin, amid, amax);
            } else if (id3 != -1) {
                val = 2;
                curve = fAcc[val][id3]->getCurve();
                table[val][id3]->getMappingValues(amin, amid, amax);
            } else {
                val = -1; // No mapping
                curve = 0;
                amin = -100.;
                amid = 0.;
                amax = 100.;
            }
        }

     public:

        APIUI() : fNumParameters(0), fHasScreenControl(false), fRedReader(0), fGreenReader(0), fBlueReader(0)
        {}

        virtual ~APIUI()
        {
            std::vector<ValueConverter*>::iterator it1;
            for (it1 = fConversion.begin(); it1 != fConversion.end(); it1++) {
                delete(*it1);
            }

            std::vector<ZoneControl*>::iterator it2;
            for (int i = 0; i < 3; i++) {
                for (it2 = fAcc[i].begin(); it2 != fAcc[i].end(); it2++) {
                    delete(*it2);
                }
                for (it2 = fGyr[i].begin(); it2 != fGyr[i].end(); it2++) {
                    delete(*it2);
                }
            }
            
            delete fRedReader;
            delete fGreenReader;
            delete fBlueReader;
        }

        // -- widget's layouts

        virtual void openTabBox(const char* label)          { fControlsLevel.push_back(label); }
        virtual void openHorizontalBox(const char* label)   { fControlsLevel.push_back(label); }
        virtual void openVerticalBox(const char* label)     { fControlsLevel.push_back(label); }
        virtual void closeBox()                             { fControlsLevel.pop_back(); }

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1);
        }

        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1);
        }

        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step);
        }

        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step);
        }

        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0);
        }

        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
			if (strcmp(key, "scale") == 0) {
                if (strcmp(val, "log") == 0) {
                    fCurrentScale = kLog;
                } else if (strcmp(val, "exp") == 0) {
                    fCurrentScale = kExp;
                } else {
                    fCurrentScale = kLin;
                }
			} else if (strcmp(key, "unit") == 0) {
				fCurrentUnit = val;
			} else if (strcmp(key, "acc") == 0) {
				fCurrentAcc = val;
			} else if (strcmp(key, "gyr") == 0) {
				fCurrentGyr = val;
			} else if (strcmp(key, "screencolor") == 0) {
                fCurrentColor = val; // val = "red", "green" or "blue"
            }
        }

        virtual void declare(const char* key, const char* val)
        {}

		//-------------------------------------------------------------------------------
		// Simple API part
		//-------------------------------------------------------------------------------
		int getParamsCount()				{ return fNumParameters; }
		int getParamIndex(const char* n) 	{ return (fMap.count(n) > 0) ? fMap[n] : -1; }
		const char* getParamAddress(int p)	{ return fName[p].c_str(); }
		const char* getParamUnit(int p)		{ return fUnit[p].c_str(); }
		FAUSTFLOAT getParamMin(int p)		{ return fMin[p]; }
		FAUSTFLOAT getParamMax(int p)		{ return fMax[p]; }
		FAUSTFLOAT getParamStep(int p)		{ return fStep[p]; }

        FAUSTFLOAT* getParamZone(int p)         { return fZone[p]; }
		FAUSTFLOAT getParamValue(int p)         { return *fZone[p]; }
		void setParamValue(int p, FAUSTFLOAT v) { *fZone[p] = v; }

		double getParamRatio(int p)         { return fConversion[p]->faust2ui(*fZone[p]); }
		void setParamRatio(int p, double r) { *fZone[p] = fConversion[p]->ui2faust(r); }

		double value2ratio(int p, double r)	{ return fConversion[p]->faust2ui(r); }
		double ratio2value(int p, double r)	{ return fConversion[p]->ui2faust(r); }

        /**
         * Set a new value coming from an accelerometer, propagate it to all relevant float* zones.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @param value - the new value
         *
         */
        void propagateAcc(int acc, double value)
        {
            for (int i = 0; i < fAcc[acc].size(); i++) {
                fAcc[acc][i]->update(value);
            }
        }
    
        /**
         * Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setAccConverter(int p, int acc, int curve, double amin, double amid, double amax)
        {
            setConverter(fAcc, p, acc, curve, amin, amid, amax);
        }
    
        /**
         * Used to edit gyroscope curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setGyrConverter(int p, int gyr, int curve, double amin, double amid, double amax)
        {
             setConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
    
        /**
         * Used to edit accelerometer curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - the acc value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getAccConverter(int p, int& acc, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fAcc, p, acc, curve, amin, amid, amax);
        }

        /**
         * Used to edit gyroscope curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param gyr - the gyr value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getGyrConverter(int p, int& gyr, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
    
        /**
         * Set a new value coming from an gyroscope, propagate it to all relevant float* zones.
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param value - the new value
         *
         */
        void propagateGyr(int gyr, double value)
        {
            for (int i = 0; i < fGyr[gyr].size(); i++) {
                fGyr[gyr][i]->update(value);
            }
        }
   
        // getScreenColor() : -1 means no screen color control (no screencolor metadata found)
        // otherwise return 0x00RRGGBB a ready to use color
        int getScreenColor()
        {
            if (fHasScreenControl) {
                int r = (fRedReader) ? fRedReader->getValue() : 0;
                int g = (fGreenReader) ? fGreenReader->getValue() : 0;
                int b = (fBlueReader) ? fBlueReader->getValue() : 0;
                return (r<<16) | (g<<8) | b;
            } else {
                return -1;
            }
        }

};

#endif
/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/
/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 
 ************************************************************************
 ************************************************************************/

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <math.h>
#include <float.h>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <string>
#include <utility>
#include <iostream>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_GUI_H
#define FAUST_GUI_H

/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#ifndef __ring_buffer__
#define __ring_buffer__

#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buf;
    size_t len;
}
ringbuffer_data_t;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
ringbuffer_t;

ringbuffer_t *ringbuffer_create(size_t sz);
void ringbuffer_free(ringbuffer_t *rb);
void ringbuffer_get_read_vector(const ringbuffer_t *rb,
                                         ringbuffer_data_t *vec);
void ringbuffer_get_write_vector(const ringbuffer_t *rb,
                                          ringbuffer_data_t *vec);
size_t ringbuffer_read(ringbuffer_t *rb, char *dest, size_t cnt);
size_t ringbuffer_peek(ringbuffer_t *rb, char *dest, size_t cnt);
void ringbuffer_read_advance(ringbuffer_t *rb, size_t cnt);
size_t ringbuffer_read_space(const ringbuffer_t *rb);
int ringbuffer_mlock(ringbuffer_t *rb);
void ringbuffer_reset(ringbuffer_t *rb);
void ringbuffer_reset_size (ringbuffer_t * rb, size_t sz);
size_t ringbuffer_write(ringbuffer_t *rb, const char *src,
                                 size_t cnt);
void ringbuffer_write_advance(ringbuffer_t *rb, size_t cnt);
size_t ringbuffer_write_space(const ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two.  */

inline ringbuffer_t *
ringbuffer_create (size_t sz)
{
	size_t power_of_two;
	ringbuffer_t *rb;

	if ((rb = (ringbuffer_t *) malloc (sizeof (ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1u; 1u << power_of_two < sz; power_of_two++);

	rb->size = 1u << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

inline void
ringbuffer_free (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

inline int
ringbuffer_mlock (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

inline void
ringbuffer_reset (ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

inline void
ringbuffer_reset_size (ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading.  This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

inline size_t
ringbuffer_read_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing.  This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

inline size_t
ringbuffer_write_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader.  Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

inline size_t
ringbuffer_read (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance.  Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

inline size_t
ringbuffer_peek (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer.  Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

inline size_t
ringbuffer_write (ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

inline void
ringbuffer_read_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

inline void
ringbuffer_write_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader.  `vec' is an array of two places.  Set
   the values at `vec' to hold the current readable data at `rb'.  If
   the readable data is in one segment the second segment has zero
   length.  */

inline void
ringbuffer_get_read_vector (const ringbuffer_t * rb,
				 ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer.  `vec' is an array of two places.  Set
   the values at `vec' to hold the current writeable data at `rb'.  If
   the writeable data is in one segment the second segment has zero
   length.  */

inline void
ringbuffer_get_write_vector (const ringbuffer_t * rb,
				  ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __ring_buffer__

#include <list>
#include <map>
#include <vector>

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

class clist : public std::list<uiItem*>
{
    public:
    
        virtual ~clist();
        
};

typedef std::map<FAUSTFLOAT*, clist*> zmap;

typedef std::map<FAUSTFLOAT*, ringbuffer_t*> ztimedmap;

class GUI : public UI
{
		
    private:
     
        static std::list<GUI*>  fGuiList;
        zmap                    fZoneMap;
        bool                    fStopped;
        
     public:
            
        GUI() : fStopped(false) 
        {	
            fGuiList.push_back(this);
        }
        
        virtual ~GUI() 
        {   
            // delete all 
            zmap::iterator g;
            for (g = fZoneMap.begin(); g != fZoneMap.end(); g++) {
                delete (*g).second;
            }
            // suppress 'this' in static fGuiList
            fGuiList.remove(this);
        }

        // -- registerZone(z,c) : zone management
        
        void registerZone(FAUSTFLOAT* z, uiItem* c)
        {
            if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
            fZoneMap[z]->push_back(c);
        } 	

        void updateAllZones();
        
        void updateZone(FAUSTFLOAT* z);
        
        static void updateAllGuis()
        {
            std::list<GUI*>::iterator g;
            for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
                (*g)->updateAllZones();
            }
        }
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data);
        virtual void show() {};	
        virtual void run() {};
        
        virtual void stop()		{ fStopped = true; }
        bool stopped() 	{ return fStopped; }

        virtual void declare(FAUSTFLOAT* , const char* , const char*) {}
        
        // Static global for timed zones, shared between all UI that will set timed values
        static ztimedmap gTimedZoneMap;

};

/**
 * User Interface Item: abstract definition
 */

class uiItem
{
    protected:
          
        GUI*            fGUI;
        FAUSTFLOAT*     fZone;
        FAUSTFLOAT      fCache;

        uiItem(GUI* ui, FAUSTFLOAT* zone) : fGUI(ui), fZone(zone), fCache(FAUSTFLOAT(-123456.654321)) 
        { 
            ui->registerZone(zone, this); 
        }

    public:

        virtual ~uiItem() 
        {}

        void modifyZone(FAUSTFLOAT v) 	
        { 
            fCache = v;
            if (*fZone != v) {
                *fZone = v;
                fGUI->updateZone(fZone);
            }
        }
                
        FAUSTFLOAT		cache()	{ return fCache; }
        virtual void 	reflectZone() = 0;	
};

/**
 * Callback Item
 */

struct uiCallbackItem : public uiItem
{
	uiCallback	fCallback;
	void*		fData;
	
	uiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data) 
			: uiItem(ui, zone), fCallback(foo), fData(data) {}
	
	virtual void reflectZone() 
    {		
		FAUSTFLOAT 	v = *fZone;
		fCache = v; 
		fCallback(v, fData);	
	}
};

/**
 * Allows to group a set of zones.
 */
 
class uiGroupItem : public uiItem 
{
    protected:
    
        std::vector<FAUSTFLOAT*> fZoneMap;

    public:
    
        uiGroupItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
        virtual ~uiGroupItem() 
        {}
        
        virtual void reflectZone() 
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            
            // Update all zones of the same group
            std::vector<FAUSTFLOAT*>::iterator it;
            for (it = fZoneMap.begin(); it != fZoneMap.end(); it++) {
                (*(*it)) = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// en cours d'installation de callback : a finir!!!!!

/**
 * Update all user items reflecting zone z
 */

inline void GUI::updateZone(FAUSTFLOAT* z)
{
	FAUSTFLOAT v = *z;
	clist* l = fZoneMap[z];
	for (clist::iterator c = l->begin(); c != l->end(); c++) {
		if ((*c)->cache() != v) (*c)->reflectZone();
	}
}

/**
 * Update all user items not up to date
 */

inline void GUI::updateAllZones()
{
	for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++) {
		FAUSTFLOAT* z = m->first;
		clist*	l = m->second;
        if (z) {
            FAUSTFLOAT	v = *z;
            for (clist::iterator c = l->begin(); c != l->end(); c++) {
                if ((*c)->cache() != v) (*c)->reflectZone();
            }
        }
	}
}

inline void GUI::addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data) 
{ 
	new uiCallbackItem(this, zone, foo, data); 
};

inline clist::~clist() 
{
    std::list<uiItem*>::iterator it;
    for (it = begin(); it != end(); it++) {
        delete (*it);
    }
}

// For precise timestamped control
struct DatedControl {

    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}

};
  
#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>

class MapUI;

//----------------------------------------------------------------
//  MIDI processor definition
//----------------------------------------------------------------

class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 127)
        {
            keyOff(channel, pitch, velocity);
        }
        
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
       
        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
        
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
       
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }

        // MIDI sync
        virtual void start_sync(double date)  {}
        virtual void stop_sync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return 0; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}

        enum MidiStatus {

            // channel voice messages
            MIDI_NOTE_OFF           = 0x80,
            MIDI_NOTE_ON            = 0x90,
            MIDI_CONTROL_CHANGE     = 0xB0,
            MIDI_PROGRAM_CHANGE     = 0xC0,
            MIDI_PITCH_BEND         = 0xE0,
            MIDI_AFTERTOUCH         = 0xD0,	// aka channel pressure
            MIDI_POLY_AFTERTOUCH    = 0xA0,	// aka key pressure
            MIDI_CLOCK              = 0xF8,
            MIDI_START              = 0xFA,
            MIDI_STOP               = 0xFC

        };

        enum MidiCtrl {

            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120

        };
};

//----------------------------------------------------------------
//  Base class for MIDI API handling
//----------------------------------------------------------------

class midi_handler : public midi {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;

    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}

        virtual void addMidiIn(midi* midi_dsp) { fMidiInputs.push_back(midi_dsp); }
        virtual void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        virtual bool start_midi() { return false; }
        virtual void stop_midi() {}
        
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->clock(time);
                }
            } else if (type == MIDI_START) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->start_sync(time);
                }
            } else if (type == MIDI_STOP) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->stop_sync(time);
                }
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->progChange(time, channel, data1);
                }
            } else if (type == MIDI_AFTERTOUCH) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->chanPress(time, channel, data1);
                }
            }
        }

        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF || ((type == MIDI_NOTE_ON) && (data2 == 0))) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOff(time, channel, data1, data2);
                }
            } else if (type == MIDI_NOTE_ON) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            } else if (type == MIDI_CONTROL_CHANGE) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            } else if (type == MIDI_PITCH_BEND) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->pitchWheel(time, channel, (data2 * 128.0) + data1);
                }
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyPress(time, channel, data1, data2);
                }
            }
        }


};

#endif // __midi__

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently "ctrl, keyon, keypress, pgm, chanpress, pitchwheel/pitchbend meta data is handled.
 ******************************************************************************/
 
class uiMidiItem : public uiItem {
 
    protected:
    
         midi* fMidiOut;
         bool fInputCtrl;

    public:
    
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input)
            :uiItem(ui, zone), fMidiOut(midi_out), fInputCtrl(input) {}
        virtual ~uiMidiItem() {}
 
};
 
class uiMidiTimedItem : public uiMidiItem
{
    protected:
    
        bool fDelete;
   
    public:
       
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input)
        {
            if (GUI::gTimedZoneMap.find(fZone) == GUI::gTimedZoneMap.end()) {
                GUI::gTimedZoneMap[fZone] = ringbuffer_create(8192);
                fDelete = true;
            } else {
                fDelete = false;
            }
        }
        
        virtual ~uiMidiTimedItem() 
        {
            ztimedmap::iterator it;
            if (fDelete && ((it = GUI::gTimedZoneMap.find(fZone)) != GUI::gTimedZoneMap.end())) {
                ringbuffer_free((*it).second);
                GUI::gTimedZoneMap.erase(it);
            }
        }

        void modifyZone(double date, FAUSTFLOAT v) 	
        { 
            size_t res;
            DatedControl dated_val(date, v);
            if ((res = ringbuffer_write(GUI::gTimedZoneMap[fZone], (const char*)&dated_val, sizeof(DatedControl))) != sizeof(DatedControl)) {
                std::cout << "ringbuffer_write error DatedControl" << std::endl;
            }
        }
        
        // TODO
        virtual void reflectZone() {}

};

// MIDI sync

class uiMidiStart : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStart(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStart()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->start_sync(0);
            }
        }
        
};

class uiMidiStop : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStop(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStop()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(1)) {
                fMidiOut->stop_sync(0);
            }
        }
};

class uiMidiClock : public uiMidiTimedItem
{

    private:
        
        bool fState;
  
    public:
    
        uiMidiClock(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fState(false)
        {}
        virtual ~uiMidiClock()
        {}
        
        void modifyZone(double date, FAUSTFLOAT v) 	
        { 
            if (fInputCtrl) {
                fState = !fState;
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fState));
            }
        }
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->clock(0);
        }
};

class uiMidiProgChange : public uiMidiItem
{
    private:
        
        int fPgm;
  
    public:
    
        uiMidiProgChange(midi* midi_out, int pgm, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input), fPgm(pgm)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->progChange(0, fPgm);
            }
        }
        
};

class uiMidiChanPress : public uiMidiItem
{
    private:
        
        int fPress;
  
    public:
    
        uiMidiChanPress(midi* midi_out, int press, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input), fPress(press)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->chanPress(0, fPress);
            }
        }
        
};

class uiMidiCtrlChange : public uiMidiItem
{
    private:
    
        int fCtrl;
        LinearValueConverter fConverter;
 
    public:
    
        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input), fCtrl(ctrl), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->ctrlChange(0, fCtrl, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
 
};

class uiMidiPitchWheel : public uiMidiItem
{

    private:
    
        LinearValueConverter fConverter;
 
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input), fConverter(0., 16383, double(min), double(max))
        {}
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->pitchWheel(0, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
 
};

class uiMidiKeyOn : public uiMidiItem
{

    private:
        
        int fKeyOn;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input), fKeyOn(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOn(0, fKeyOn, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
        
};

class uiMidiKeyOff : public uiMidiItem
{

    private:
        
        int fKeyOff;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input), fKeyOff(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOff(0, fKeyOff, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
        
};

class uiMidiKeyPress : public uiMidiItem
{

    private:
        
        int fKeyOn;
        LinearValueConverter fConverter;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
            :uiMidiItem(midi_out, ui, zone, input), fKeyOn(key), fConverter(0., 127., double(min), double(max))
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyPress(0, fKeyOn, fConverter.faust2ui(v));
        }
        
        void modifyZone(int v) 	
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
        
};

class MapUI;

class MidiUI : public GUI, public midi
{

    protected:
    
        std::map <int, std::vector<uiMidiCtrlChange*> > fCtrlChangeTable;
        std::map <int, std::vector<uiMidiProgChange*> > fProgChangeTable;
        std::map <int, std::vector<uiMidiChanPress*> >  fChanPressTable;
        std::map <int, std::vector<uiMidiKeyOn*> >      fKeyOnTable;
        std::map <int, std::vector<uiMidiKeyOff*> >     fKeyOffTable;
        std::map <int, std::vector<uiMidiKeyPress*> >   fKeyPressTable;
        std::vector<uiMidiPitchWheel*>                  fPitchWheelTable;
        
        std::vector<uiMidiStart*>   fStartTable;
        std::vector<uiMidiStop*>    fStopTable;
        std::vector<uiMidiClock*>   fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    if (fMetaAux[i].first == "midi") {
                        if (sscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "pgm %u", &num) == 1) {
                            fProgChangeTable[num].push_back(new uiMidiProgChange(fMidiHandler, num, this, zone, input));
                        } else if (sscanf(fMetaAux[i].second.c_str(), "chanpress %u", &num) == 1) {
                            fChanPressTable[num].push_back(new uiMidiChanPress(fMidiHandler, num, this, zone, input));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "pitchwheel") == 0 
                            || strcmp(fMetaAux[i].second.c_str(), "pitchbend") == 0) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input));
                        // MIDI sync
                        } else if (strcmp(fMetaAux[i].second.c_str(), "start") == 0) {
                            fStartTable.push_back(new uiMidiStart(fMidiHandler, this, zone, input));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "stop") == 0) {
                            fStopTable.push_back(new uiMidiStop(fMidiHandler, this, zone, input));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "clock") == 0) {
                            fClockTable.push_back(new uiMidiClock(fMidiHandler, this, zone, input));
                        }
                    }
                }
            }
            fMetaAux.clear();
        }

    public:

        MidiUI(midi_handler* midi_handler)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
        }
 
        virtual ~MidiUI() 
        { 
            fMidiHandler->removeMidiIn(this);
        }
        
        void run() { fMidiHandler->start_midi(); }
        void stop() { fMidiHandler->stop_midi(); }
        
        void addMidiIn(midi* midi_dsp) { fMidiHandler->addMidiIn(midi_dsp); }
        void removeMidiIn(midi* midi_dsp) { fMidiHandler->removeMidiIn(midi_dsp); }
      
        // -- widget's layouts

        virtual void openTabBox(const char* label)
        {}
        virtual void openHorizontalBox(const char* label)
        {}
        virtual void openVerticalBox(const char* label)
        {}
        virtual void closeBox()
        {}

        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max, false);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max, false);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API 
        
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            if (fKeyOnTable.find(note) != fKeyOnTable.end()) {
                for (unsigned int i = 0; i < fKeyOnTable[note].size(); i++) {
                    fKeyOnTable[note][i]->modifyZone(FAUSTFLOAT(velocity));
                }
            }
            return 0;
        }
        
        void keyOff(double date,  int channel, int note, int velocity)
        {
            if (fKeyOffTable.find(note) != fKeyOffTable.end()) {
                for (unsigned int i = 0; i < fKeyOffTable[note].size(); i++) {
                    fKeyOffTable[note][i]->modifyZone(FAUSTFLOAT(velocity));
                }
            }
        }
           
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            if (fCtrlChangeTable.find(ctrl) != fCtrlChangeTable.end()) {
                for (unsigned int i = 0; i < fCtrlChangeTable[ctrl].size(); i++) {
                    fCtrlChangeTable[ctrl][i]->modifyZone(FAUSTFLOAT(value));
                }
            } 
        }
        
        void progChange(double date, int channel, int pgm)
        {
            if (fProgChangeTable.find(pgm) != fProgChangeTable.end()) {
                for (unsigned int i = 0; i < fProgChangeTable[pgm].size(); i++) {
                    fProgChangeTable[pgm][i]->modifyZone(FAUSTFLOAT(1));
                }
            } 
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            for (unsigned int i = 0; i < fPitchWheelTable.size(); i++) {
                fPitchWheelTable[i]->modifyZone(FAUSTFLOAT(wheel));
            }
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            if (fKeyPressTable.find(press) != fKeyPressTable.end()) {
                for (unsigned int i = 0; i < fKeyPressTable[press].size(); i++) {
                    fKeyPressTable[press][i]->modifyZone(FAUSTFLOAT(press));
                }
            } 
        }
        
        void chanPress(double date, int channel, int press)
        {
            if (fChanPressTable.find(press) != fChanPressTable.end()) {
                for (unsigned int i = 0; i < fChanPressTable[press].size(); i++) {
                    fChanPressTable[press][i]->modifyZone(FAUSTFLOAT(1));
                }
            } 
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void start_sync(double date)
        {
            for (unsigned int i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stop_sync(double date)
        {
            for (unsigned int i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (unsigned int i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <map>
#include <string>


/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, float value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        float getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return 0.;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return fPathZoneMap.size(); }
        
        std::string getParamAdress(int index) 
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
};

#endif // FAUST_MAPUI_H
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>

/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

// ---------------------------------------------------------------------
//                          Simple Parser
// A parser returns true if it was able to parse what it is
// supposed to parse and advance the pointer. Otherwise it returns false
// and the pointer is not advanced so that another parser can be tried.
// ---------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <ctype.h>

using namespace std;

struct itemInfo {
    std::string type;
    std::string label;
    std::string address;
    std::string init;
    std::string min;
    std::string max;
    std::string step;
    std::vector<std::pair<std::string, std::string> > meta;
};

bool parseMenuList(const char*& p, vector<string>& names, vector<double>& values);
bool parseMenuItem(const char*& p, string& name, double& value);

void skipBlank(const char*& p);
bool parseChar(const char*& p, char x);
bool parseWord(const char*& p, const char* w);
bool parseString(const char*& p, char quote, string& s);
bool parseSQString(const char*& p, string& s);
bool parseDQString(const char*& p, string& s);
bool parseDouble(const char*& p, double& x);

// ---------------------------------------------------------------------
//
//                          IMPLEMENTATION
// 
// ---------------------------------------------------------------------

/**
 * @brief parseMenuList, parse a menu list {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}...
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of values found
 * @return true if a menu list was found
 */
inline bool parseMenuList(const char*& p, vector<string>& names, vector<double>& values)
{
    vector<string> tmpnames;
    vector<double> tmpvalues;

    const char* saved = p;

    if (parseChar(p, '{')) {
        do {
            string n;
            double v;
            if (parseMenuItem(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseMenuItem, parse a menu item ...'low':440.0...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found
 * @return true if a nemu item was found
 */
inline bool parseMenuItem(const char*& p, string& name, double& value)
{
    const char* saved = p;
    if (parseSQString(p, name) && parseChar(p, ':') && parseDouble(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    std::cerr << "Parse error : " << errmsg << " here : " << p << std::endl;
    return true;
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief skipBlank : advance pointer p to the first non blank character
 * @param p the string to parse, then the remaining string
 */
inline void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

/**
 * @brief parseChar : parse a specific character x
 * @param p the string to parse, then the remaining string
 * @param x the character to recognize
 * @return true if x was found at the begin of p
 */
inline bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseWord : parse a specific string w
 * @param p the string to parse, then the remaining string
 * @param w the string to recognize
 * @return true if string w was found at the begin of p
 */
inline bool parseWord(const char*& p, const char* w)
{
    skipBlank(p);
    const char* saved = p;
    while ((*w == *p) && (*w)) {++w; ++p;}
    if (*w) {
        p = saved;
        return false;
    } else {
        return true;
    }
}

/**
 * @brief parseDouble : parse number [s]dddd[.dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
inline bool parseDouble(const char*& p, double& x)
{
    double sign = +1.0;    // sign of the number
    double ipart = 0;      // integral part of the number
    double dpart = 0;      // decimal part of the number before division
    double dcoef = 1.0;    // division factor for the decimal part

    bool valid = false;   // true if the number contains at least one digit
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail

    if (parseChar(p, '+')) {
        sign = 1.0;
    } else if (parseChar(p, '-')) {
        sign = -1.0;
    }
    while (isdigit(*p)) {
        valid = true;
        ipart = ipart*10 + (*p - '0');
        p++;
    }
    if (parseChar(p, '.')) {
        while (isdigit(*p)) {
            valid = true;
            dpart = dpart*10 + (*p - '0');
            dcoef *= 10.0;
            p++;
        }
    }
    if (valid)  {
        x = sign*(ipart + dpart/dcoef);
    } else {
        p = saved;
    }
    return valid;
}

/**
 * @brief parseString, parse an arbitrary quoted string q...q and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
inline bool parseString(const char*& p, char quote, string& s)
{
    string str;
    skipBlank(p);
 
    const char* saved = p;
    if (*p++ == quote) {
        while ((*p != 0) && (*p != quote)) {
            str += *p++;
        }
        if (*p++ == quote) {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseSQString, parse a single quoted string '...' and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
inline bool parseSQString(const char*& p, string& s)
{
    return parseString(p, '\'', s);
}

/**
 * @brief parseDQString, parse a double quoted string "..." and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
inline bool parseDQString(const char*& p, string& s)
{
    return parseString(p, '"', s);
}

static bool parseMetaData(const char*& p, std::map<std::string, std::string>& metadatas)
{
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
//
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, std::map<std::string, std::string>& metadatas)
{
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && parseDQString(p, value);
        }
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
//
static bool parseUI(const char*& p, std::vector<itemInfo*>& uiItems, int& numItems)
{
    if (parseChar(p, '{')) {
        
        std::string label;
        std::string value;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo* item = new itemInfo;
                        item->type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->label = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->address = value;
                    }
                }
                
                else if (label == "meta") {
                    itemInfo* item = uiItems[numItems];
                    if (!parseItemMetaData(p, item->meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->init = value;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->min = value;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->max = value;
                    }
                }
                
                else if (label == "step"){
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        itemInfo* item = uiItems[numItems];
                        item->step = value;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do { 
                            if (!parseUI(p, uiItems, numItems)) {
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo* item = new itemInfo;
                            item->type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                return false;
            }
            
        } while (tryChar(p, ','));
        
        return parseChar(p, '}');
    } else {
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
//

inline bool parseJson(const char*& p, std::map<std::string, std::string>& metadatas, std::vector<itemInfo*>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        if (parseGlobalMetaData(p, key, value, metadatas)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                metadatas[key] = value;
            }
        } else if (key == "ui") {
            int numItems = 0;
            parseChar(p, '[') && parseUI(p, uiItems, numItems);
        }
    } while (tryChar(p, ','));
    
    return parseChar(p, '}');
}

#endif // SIMPLEPARSER_H

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

inline FAUSTFLOAT STR2REAL(const std::string& s)  { return (strtod(s.c_str(), NULL)); }

//-------------------------------------------------------------------
//  Decode a dsp JSON description and implement 'buildUserInterface'
//-------------------------------------------------------------------

struct JSONUIDecoder {

    std::string fName;
    
    std::map<std::string, std::string> fMetadatas; 
    std::vector<itemInfo*> fUiItems;     
    
    FAUSTFLOAT* fInControl;
    FAUSTFLOAT* fOutControl;
    
    std::string fJSON;
    
    int fNumInputs, fNumOutputs; 
    int fInputItems, fOutputItems; 

    JSONUIDecoder(const std::string& json) 
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        parseJson(p, fMetadatas, fUiItems);
        
        // fMetadatas will contain the "meta" section as well as <name : val>, <inputs : val>, <ouputs : val> pairs
        if (fMetadatas.find("name") != fMetadatas.end()) {
            fName = fMetadatas["name"];
            fMetadatas.erase("name");
        } else {
            fName = "";
        }
         
        if (fMetadatas.find("inputs") != fMetadatas.end()) {
            fNumInputs = atoi(fMetadatas["inputs"].c_str());
            fMetadatas.erase("inputs");
        } else {
            fNumInputs = -1;
        }
        
        if (fMetadatas.find("outputs") != fMetadatas.end()) {
            fNumOutputs = atoi(fMetadatas["outputs"].c_str());
            fMetadatas.erase("outputs");
        } else {
            fNumOutputs = -1;
        }
        
        vector<itemInfo*>::iterator it;
        fInputItems = 0;
        fOutputItems = 0;
        
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            string type = (*it)->type;
            if (type == "vslider" || type == "hslider" || type == "nentry" || type == "button") {
                fInputItems++;
            } else if (type == "hbargraph" || type == "vbargraph") {
                fOutputItems++;          
            }
        }
        
        fInControl = new FAUSTFLOAT[fInputItems];
        fOutControl = new FAUSTFLOAT[fOutputItems];
    }
    
    virtual ~JSONUIDecoder() 
    {
        vector<itemInfo*>::iterator it;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            delete(*it);
        }
        delete [] fInControl;
        delete [] fOutControl;
    }
    
    void metadata(Meta* m)
    {
        std::map<std::string, std::string>::iterator it;
        for (it = fMetadatas.begin(); it != fMetadatas.end(); it++) {
            m->declare((*it).first.c_str(), (*it).second.c_str());
        }
    }
   
    void buildUserInterface(UI* ui)
    {
        // To be sure the floats are correctly encoded
        char* tmp_local = setlocale(LC_ALL, NULL);
        setlocale(LC_ALL, "C");

        int counterIn = 0;
        int counterOut = 0;
        vector<itemInfo*>::iterator it;
        
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            
            bool isInItem = false;
            bool isOutItem = false;
            string type = (*it)->type;
            
            FAUSTFLOAT init = STR2REAL((*it)->init);
            FAUSTFLOAT min = STR2REAL((*it)->min);
            FAUSTFLOAT max = STR2REAL((*it)->max);
            FAUSTFLOAT step = STR2REAL((*it)->step);
            
            if (type == "vslider" || type == "hslider" || type == "nentry" || type == "button") {
                isInItem = true;
            } else if (type == "hbargraph" || type == "vbargraph") {
                isOutItem = true;        
            }
            
            // Meta data declaration for input items
            if ((*it)->type.find("group") == string::npos && (*it)->type.find("bargraph") == string::npos && (*it)->type != "close") {
                fInControl[counterIn] = init;
                for (int i = 0; i < (*it)->meta.size(); i++) {
                    ui->declare(&fInControl[counterIn], (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if ((*it)->type.find("bargraph") != string::npos) {
                fOutControl[counterOut] = init;
                for (int i = 0; i < (*it)->meta.size(); i++) {
                    ui->declare(&fOutControl[counterOut], (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (int i = 0; i < (*it)->meta.size(); i++) {
                    ui->declare(0, (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui->openHorizontalBox((*it)->label.c_str());
            } else if (type == "vgroup") { 
                ui->openVerticalBox((*it)->label.c_str());
            } else if (type == "tgroup") {
                ui->openTabBox((*it)->label.c_str());
            } else if (type == "vslider") {
                ui->addVerticalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
            } else if (type == "hslider") {
                ui->addHorizontalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);            
            } else if (type == "checkbox") {
                ui->addCheckButton((*it)->label.c_str(), &fInControl[counterIn]);
            } else if (type == "hbargraph") {
                ui->addHorizontalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
            } else if (type == "vbargraph") {
                ui->addVerticalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
            } else if (type == "nentry") {
                ui->addNumEntry((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
            } else if (type == "button") {
                ui->addButton((*it)->label.c_str(), &fInControl[counterIn]);
            } else if (type == "close") {
                ui->closeBox();
            }
                
            if (isInItem) {
                counterIn++;
            }
                
            if (isOutItem) {
                counterOut++;
            }
        }
        
        setlocale(LC_ALL, tmp_local);
    }
    
};

//----------------------------------------------------------------
//  Proxy dsp definition created from the DSP JSON description
//  This class allows a 'proxy' dsp to control a real dsp 
//  possibly running somewhere else.
//----------------------------------------------------------------

class proxy_dsp : public dsp {

    private:
    
        int fSamplingFreq;
        JSONUIDecoder* fDecoder;
        
    public:
    
        proxy_dsp(const string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSamplingFreq = -1;
        }
          
        proxy_dsp(dsp* dsp)
        {
            JSONUI builder(dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->metadata(&builder);
            dsp->buildUserInterface(&builder);
            fSamplingFreq = dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
       
        virtual int getNumInputs() 	{ return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy dsp 
        virtual void init(int samplingRate) { fSamplingFreq = samplingRate; }
        virtual void instanceInit(int samplingRate) {}
        virtual void instanceConstants(int samplingRate) {}
        virtual void instanceResetUserInterface() {}
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSamplingFreq; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

#endif

#define kActiveVoice      0
#define kFreeVoice        -1
#define kReleaseVoice     -2
#define kNoVoice          -3

#define VOICE_STOP_LEVEL  0.001
#define MIX_BUFFER_SIZE   16384

#define FLOAT_MAX(a, b) (((a) < (b)) ? (b) : (a))

// ends_with(<str>,<end>) : returns true if <str> ends with <end>
static bool ends_with(std::string const& str, std::string const& end)
{
	unsigned int l1 = str.length();
	unsigned int l2 = end.length();
    return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
}

class GroupUI : public GUI, public PathBuilder
{
    
    private:
    
        std::map<std::string, uiGroupItem*> fLabelZoneMap;
        
        void insertMap(std::string label, FAUSTFLOAT* zone)
        {   
            if (!ends_with(label, "/gate") 
                && !ends_with(label, "/freq") 
                && !ends_with(label, "/gain")) {
                
                // Groups all controller except 'freq', 'gate', and 'gain'
                if (fLabelZoneMap.find(label) != fLabelZoneMap.end()) {
                    fLabelZoneMap[label]->addZone(zone);
                } else {
                    fLabelZoneMap[label] = new uiGroupItem(this, zone);
                }
            }
        }
        
        uiCallbackItem* fPanic;
           
    public:
        
        GroupUI(FAUSTFLOAT* zone, uiCallback cb, void* arg)
        {
            fPanic = new uiCallbackItem(this, zone, cb, arg);
        };
        virtual ~GroupUI() 
        {
            // 'fPanic' is kept and deleted in GUI, so do not delete here
        };
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
            
};

// One voice of polyphony
struct dsp_voice : public MapUI, public decorator_dsp {
    
    int fNote;          // Playing note actual pitch
    int fDate;          // KeyOn date
    bool fTrigger;      // True if stolen note and need for envelop re-trigger
    FAUSTFLOAT fLevel;  // Last audio block level

    dsp_voice(dsp* dsp):decorator_dsp(dsp)
    {
        dsp->buildUserInterface(this);
        fNote = kFreeVoice;
        fLevel = FAUSTFLOAT(0);
        fDate = 0;
        fTrigger = false;
    }
 
};

/**
 * Polyphonic DSP : group a set of DSP to be played together or triggered by MIDI.
 */

class mydsp_poly : public dsp, public midi {

    private:
    
        dsp* fBaseDSP;
        std::vector<dsp_voice*> fVoiceTable; // Individual voices
        dsp* fVoiceGroup;                    // Voices group to be used for GUI grouped control
        
        std::string fGateLabel;
        std::string fGainLabel;
        std::string fFreqLabel;
        FAUSTFLOAT fPanic;
        
        int fPolyphony;
        bool fVoiceControl;
        bool fGroupControl;
        
        GroupUI fGroups;
        
        FAUSTFLOAT** fMixBuffer;
        int fNumOutputs;
        int fDate;
        
        std::vector<MidiUI*> fMidiUIList;
        
        inline FAUSTFLOAT mixVoice(int count, FAUSTFLOAT** outputBuffer, FAUSTFLOAT** mixBuffer) 
        {
            FAUSTFLOAT level = 0;
            for (int i = 0; i < fNumOutputs; i++) {
                FAUSTFLOAT* mixChannel = mixBuffer[i];
                FAUSTFLOAT* outChannel = outputBuffer[i];
                for (int j = 0; j < count; j++) {
                    level = FLOAT_MAX(level, (FAUSTFLOAT)fabs(outChannel[j]));
                    mixChannel[j] += outChannel[j];
                }
            }
            return level;
        }
        
        inline double midiToFreq(double note) 
        {
            return 440.0 * pow(2.0, (note-69.0)/12.0);
        }
        
        inline void clearOutput(int count, FAUSTFLOAT** mixBuffer) 
        {
            for (int i = 0; i < fNumOutputs; i++) {
                memset(mixBuffer[i], 0, count * sizeof(FAUSTFLOAT));
            }
        }
          
        inline int getVoice(int note, bool steal = false)
        {
            for (int i = 0; i < fPolyphony; i++) {
                if (fVoiceTable[i]->fNote == note) {
                    if (steal) { fVoiceTable[i]->fDate = fDate++; }
                    return i;
                }
            }
             
            if (steal) {
                int voice = kNoVoice;
                int date = INT_MAX;
                for (int i = 0; i < fPolyphony; i++) {
                    // Try to steal a voice in kReleaseVoice mode...
                    if (fVoiceTable[i]->fNote == kReleaseVoice) {
                        printf("Steal release voice : voice_date = %d cur_date = %d voice = %d\n", fVoiceTable[i]->fDate, fDate, i);
                        fVoiceTable[i]->fDate = fDate++;
                        fVoiceTable[i]->fTrigger = true;
                        return i;
                    // Otherwise steal oldest voice...
                    } else if (fVoiceTable[i]->fDate < date) {
                        date = fVoiceTable[i]->fDate;
                        voice = i;
                    }
                }
                printf("Steal playing voice : voice_date = %d cur_date = %d voice = %d\n", fVoiceTable[voice]->fDate, fDate, voice);
                fVoiceTable[voice]->fDate = fDate++;
                fVoiceTable[voice]->fTrigger = true;
                return voice;
            } else {
                return kNoVoice;
            }
        }
        
        inline void init(dsp* dsp, int max_polyphony, bool control, bool group)
        {
            fBaseDSP = dsp;
            fVoiceControl = control;
            fGroupControl = group;
            fPolyphony = max_polyphony;
            fFreqLabel = fGateLabel = fGainLabel = "";
            
            // Create voices
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable.push_back(new dsp_voice(dsp->clone()));
            }
            
            // Init audio output buffers
            fNumOutputs = fVoiceTable[0]->getNumOutputs();
            fMixBuffer = new FAUSTFLOAT*[fNumOutputs];
            for (int i = 0; i < fNumOutputs; i++) {
                fMixBuffer[i] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }
            
            // Groups all uiItem for a given path
            fVoiceGroup = new proxy_dsp(fVoiceTable[0]);
            fVoiceGroup->buildUserInterface(&fGroups);
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->buildUserInterface(&fGroups);
            }
            
            fDate = 0;
            
            // Keep gain, freq and gate labels
            std::map<std::string, FAUSTFLOAT*>::iterator it;
            for (it = fVoiceTable[0]->getMap().begin(); it != fVoiceTable[0]->getMap().end(); it++) {
                std::string label = (*it).first;
                if (ends_with(label, "/gate")) {
                    fGateLabel = label;
                } else if (ends_with(label, "/freq")) {
                    fFreqLabel = label;
                } else if (ends_with(label, "/gain")) {
                    fGainLabel = label;
                }
            }
        }
        
        void uIBuilder(UI* ui_interface)
        {
            ui_interface->openTabBox("Polyphonic");
            
            // Grouped voices UI
            ui_interface->openVerticalBox("Voices");
            ui_interface->addButton("Panic", &fPanic);
            fVoiceGroup->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            
            // In not group, also add individual voices UI
            if (!fGroupControl) {
                for (int i = 0; i < fPolyphony; i++) {
                    char buffer[32];
                    snprintf(buffer, 31, ((fPolyphony < 8) ? "Voice%d" : "V%d"), i+1);
                    ui_interface->openHorizontalBox(buffer);
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
            }
            
            ui_interface->closeBox();
        }
        
        static void panic(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<mydsp_poly*>(arg)->allNotesOff();
            }
        }
        
        inline bool checkPolyphony() 
        {
            if (fFreqLabel == "") {
                printf("DSP is not polyphonic...\n");
                return false;
            } else {
                return true;;
            }
        }
        
        inline void computeSlice(dsp* dsp, int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            if (slice > 0) {
                FAUSTFLOAT** inputs_slice = (FAUSTFLOAT**)alloca(dsp->getNumInputs() * sizeof(FAUSTFLOAT*));
                for (int chan = 0; chan < dsp->getNumInputs(); chan++) {
                    inputs_slice[chan] = &(inputs[chan][offset]);
                }
                
                FAUSTFLOAT** outputs_slice = (FAUSTFLOAT**)alloca(dsp->getNumOutputs() * sizeof(FAUSTFLOAT*));
                for (int chan = 0; chan < dsp->getNumOutputs(); chan++) {
                    outputs_slice[chan] = &(outputs[chan][offset]);
                }
                
                dsp->compute(slice, inputs_slice, outputs_slice);
            } 
        }
        
        inline unsigned int isPowerOfTwo(unsigned int n)
        {
            return !(n & (n - 1));
        }
    
        // Always returns a voice
        int newVoiceAux()
        {
            int voice = getVoice(kFreeVoice, true);
            assert(voice != kNoVoice);
            fVoiceTable[voice]->fNote = kActiveVoice;
            return voice;
        }
    
    public:
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be used for one voice. Beware : mydsp_poly will use and finally delete the pointer.
         * @param max_polyphony - number of voices of polyphony
         * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler). 
         *                 If false all voices are always running.
         * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
         *                 a given control on all voices, assuming GUI::updateAllGuis() is called.
         *                If false, all voices can be individually controlled.
         *
         */
        mydsp_poly(dsp* dsp,
                int max_polyphony,
                bool control = false,   
                bool group = true):fGroups(&fPanic, panic, this)
        {
            init(dsp, max_polyphony, control, group);
        }
    
        void metadata(Meta* meta) { fVoiceTable[0]->metadata(meta); }

        virtual ~mydsp_poly()
        {
            for (int i = 0; i < fNumOutputs; i++) {
                delete[] fMixBuffer[i];
            }
            delete[] fMixBuffer;
            
            for (int i = 0; i < fPolyphony; i++) {
                delete fVoiceTable[i];
            }
            
            delete fVoiceGroup;
            
            // Remove object from all MidiUI interfaces that handle it
            for (int i = 0; i < fMidiUIList.size(); i++) {
                fMidiUIList[i]->removeMidiIn(this); 
            }
            
            delete fBaseDSP;
        }
    
        void init(int sample_rate)
        {
            // Init voices
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->init(sample_rate);
            }
        }
    
        void instanceInit(int sample_rate)
        {
            // Init voices
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->instanceInit(sample_rate);
            }
        }
    
        void instanceConstants(int sample_rate)
        {
            // Init voices
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->instanceConstants(sample_rate);
            }
        }
    
        void instanceResetUserInterface()
        {
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->instanceResetUserInterface();
            }
        }
    
        void instanceClear()
        {
            for (int i = 0; i < fPolyphony; i++) {
                fVoiceTable[i]->instanceClear();
            }
        }
    
        virtual int getSampleRate() { return fVoiceTable[0]->getSampleRate(); }
    
        virtual mydsp_poly* clone()
        {
            return new mydsp_poly(fBaseDSP, fPolyphony, fVoiceControl, fGroupControl);
        }
    
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count < MIX_BUFFER_SIZE);
            
            // First clear the outputs
            clearOutput(count, outputs);
            
            if (fVoiceControl) {
                // Mix all playing voices
                for (int i = 0; i < fPolyphony; i++) {
                    if (fVoiceTable[i]->fNote != kFreeVoice) {
                        if (fVoiceTable[i]->fTrigger) {
                            //If stolen note and need for envelop re-trigger
                            int slice = isPowerOfTwo(count) ? count/2 : 1;
                            fVoiceTable[i]->setParamValue(fGateLabel, 0.0f);
                            computeSlice(fVoiceTable[i], 0, slice, inputs, fMixBuffer);
                            fVoiceTable[i]->setParamValue(fGateLabel, 1.0f);
                            computeSlice(fVoiceTable[i], slice, count - slice, inputs, fMixBuffer);
                            fVoiceTable[i]->fTrigger = false;
                        } else {
                            // Compute regular voice
                            fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                        }
                        // Mix it in result
                        fVoiceTable[i]->fLevel = mixVoice(count, fMixBuffer, outputs);
                        // Check the level to possibly set the voice in kFreeVoice again
                        if ((fVoiceTable[i]->fLevel < VOICE_STOP_LEVEL) && (fVoiceTable[i]->fNote == kReleaseVoice)) {
                            fVoiceTable[i]->fNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (int i = 0; i < fPolyphony; i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, outputs);
                }
            }
        }
        
        int getNumInputs()
        {
            return fVoiceTable[0]->getNumInputs();
        }
        
        int getNumOutputs()
        {
            return fVoiceTable[0]->getNumOutputs();
        }
        
        void buildUserInterface(UI* ui_interface) 
        {   
            // Add itself to the MidiUI object
            MidiUI* midi_ui = dynamic_cast<MidiUI*>(ui_interface);
            if (midi_ui) { 
                fMidiUIList.push_back(midi_ui);
                midi_ui->addMidiIn(this); 
            }
            
            if (fPolyphony > 1) {
                uIBuilder(ui_interface);
            } else {
                fVoiceTable[0]->buildUserInterface(ui_interface);
            }
        }
    
        MapUI* newVoice()
        {
            return fVoiceTable[newVoiceAux()];
        }
        
        void deleteVoice(MapUI* voice)
        {
            std::vector<dsp_voice*>::iterator it = find(fVoiceTable.begin(), fVoiceTable.end(), reinterpret_cast<dsp_voice*>(voice));
            if (it != fVoiceTable.end()) {
                (*it)->setParamValue(fGateLabel, 0.0f);
                // Release voice
                (*it)->fNote = kReleaseVoice;
            } else {
                printf("Voice not found\n");
            }
        }
        
        // Pure MIDI control
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = newVoiceAux();
                fVoiceTable[voice]->setParamValue(fFreqLabel, midiToFreq(pitch));
                fVoiceTable[voice]->setParamValue(fGainLabel, float(velocity)/127.f);
                fVoiceTable[voice]->setParamValue(fGateLabel, 1.0f);
                fVoiceTable[voice]->fNote = pitch;
                return fVoiceTable[voice];
            }
            
            return 0;
        }
        
        void keyOff(int channel, int pitch, int velocity = 127)
        {
            if (checkPolyphony()) {
                int voice = getVoice(pitch);
                if (voice != kNoVoice) {
                    // No use of velocity for now...
                    fVoiceTable[voice]->setParamValue(fGateLabel, 0.0f);
                    // Release voice
                    fVoiceTable[voice]->fNote = kReleaseVoice;
                } else {
                    printf("Playing pitch = %d not found\n", pitch);
                }
            }
        }
        
        void pitchWheel(int channel, int wheel)
        {}
         
        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }
        
        void progChange(int channel, int pgm)
        {}
        
        void keyPress(int channel, int pitch, int press)
        {}
        
        void chanPress(int channel, int press)
        {}
         
        void ctrlChange14bits(int channel, int ctrl, int value)
        {}
 
        // Additional API
        void allNotesOff()
        {
            if (checkPolyphony()) {
                for (int i = 0; i < fPolyphony; i++) {
                    fVoiceTable[i]->setParamValue(fGateLabel, 0.0f);
                    fVoiceTable[i]->fNote = kReleaseVoice;
                    fVoiceTable[i]->fTrigger = false;
                }
            }
        }
};

#endif // __poly_dsp__

//**************************************************************
// Mono or polyphonic audio DSP engine
//**************************************************************

#ifndef POLY_VOICES
#define POLY_VOICES 0 	// default is no polyphony (mono)
#endif

using namespace std;

class FaustPolyEngine {
        
    protected:

        mydsp* fMonoDSP;          // the monophonic Faust object
        mydsp_poly* fPolyDSP;     // the polyphonic Faust object
        dsp* fFinalDSP;           // the "final" dsp object submitted to the audio driver
        APIUI fAPIUI;             // the UI description

        string fJSON;
        bool fRunning;
        int fPolyMax;
        audio* fDriver;
    
    public:

        FaustPolyEngine()
        {
            fRunning = false;
            fMonoDSP = new mydsp();

            // Configuring the UI
            JSONUI jsonui1(fMonoDSP->getNumInputs(), fMonoDSP->getNumOutputs());
            fMonoDSP->buildUserInterface(&jsonui1);
            fJSON = jsonui1.JSON();

            if (fJSON.find("keyboard") != std::string::npos
                || fJSON.find("poly") != std::string::npos
                || POLY_VOICES != 0) {
                
                if (POLY_VOICES != 0) {
                    fPolyMax = POLY_VOICES;
                } else {
                    fPolyMax = 10; // default number of poly voices
                }

                fPolyDSP = new mydsp_poly(fMonoDSP, fPolyMax, true);

            #if POLY2
                fFinalDSP = new dsp_sequencer(fPolyDSP, new effect());
            #else
                fFinalDSP = fPolyDSP;
            #endif
                
                // Update JSON with Poly version
                JSONUI jsonui2(fMonoDSP->getNumInputs(), fMonoDSP->getNumOutputs());
                fFinalDSP->buildUserInterface(&jsonui2);
                fJSON = jsonui2.JSON();
                
            } else {
                fPolyMax = 0;
                fPolyDSP = NULL;
                fFinalDSP = fMonoDSP;
            }
            fFinalDSP->buildUserInterface(&fAPIUI);
         }

        virtual ~FaustPolyEngine()
        {
            delete fFinalDSP;
            delete fDriver;
        }
    
        /*
         * init()
         * Initialize the underlying audio driver with the DSP.
         */
        bool init()
        {
            return fDriver->init("Dummy", fFinalDSP);
        }

        /*
         * start()
         * Begins the processing and return true if the connection
         * with the audio device was successful and false if not.
         */
        bool start()
        {
            if (!fRunning) {
                fRunning = fDriver->start();
            }
            return fRunning;
        }
        
        /*
         * isRunning()
         * Returns true if the DSP frames are being computed and
         * false if not.
         */
        bool isRunning() 
        {
            return fRunning;
        }

        /*
         * stop()
         * Stops the processing, closes the audio engine.
         */
        void stop()
        {
            if (fRunning) {
                fRunning = false;
                fDriver->stop();
            }
        }
    
        /*
         * keyOn(pitch, velocity)
         * Instantiates a new polyphonic voice where velocity
         * and pitch are MIDI numbers (0-127). keyOn can only
         * be used if the [style:poly] metadata is used in the
         * Faust code. keyOn will return 0 if the object is not
         * polyphonic and the allocated voice otherwise.
         */
        MapUI* keyOn(int pitch, int velocity)
        {
            if (fPolyMax > 0) {
                return fPolyDSP->keyOn(0, pitch, velocity); // MapUI* passed to Java as an integer
            } else {
                return 0;
            }
        }

        /*
         * keyOff(pitch)
         * De-instantiates a polyphonic voice where pitch is the
         * MIDI number of the note (0-127). keyOff can only be
         * used if the [style:poly] metadata is used in the Faust
         * code. keyOn will return 0 if the object is not polyphonic
         * and 1 otherwise.
         */
        int keyOff(int pitch, int velocity = 127)
        {
            if (fPolyMax > 0) {
                fPolyDSP->keyOff(0, pitch, velocity);
                return 1;
            } else {
                return 0;
            }
        }
    
        /*
         * getJSON()
         * Returns a string containing a JSON description of the
         * UI of the Faust object.
         */
        const char* getJSON()
        {
            return fJSON.c_str();
        }
    
        /*
         * buildUserInterface(ui)
         * Calls the polyphonic of monophonic buildUserInterface with the ui parameter.
         */
        void buildUserInterface(UI* ui_interface)
        {
            if (fPolyMax > 0) {
                fPolyDSP->buildUserInterface(ui_interface);
            } else {
                fMonoDSP->buildUserInterface(ui_interface);
            }
        }

        /*
         * getParamsCount()
         * Returns the number of control parameters of the Faust object.
         */
        int getParamsCount()
        {
            return fAPIUI.getParamsCount();
        }
    
        /*
         * setParam(address, value)
         * Sets the value of the parameter associated with address.
         */
        void setParamValue(const char* address, float value)
        {
            fAPIUI.setParamValue(fAPIUI.getParamIndex(address), value);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }

        /*
         * getParamValue(address)
         * Takes the address of a parameter and returns its current
         * value.
         */
        float getParamValue(const char* address)
        {
            return fAPIUI.getParamValue(fAPIUI.getParamIndex(address));
        }

        /*
         * setVoiceParamValue(address, voice, value)
         * Sets the value of the parameter associated with address for
         * the voice. setVoiceParamValue can only be
         * used if the [style:poly] metadata is used in the Faust code.
         */
        void setVoiceParamValue(const char* address, int voice, float value)
        {
            assert(sizeof(int) == sizeof(MapUI*));
            reinterpret_cast<MapUI*>(voice)->setParamValue(address, value);
        }
    
        /*
         * getVoiceParamValue(address, voice)
         * Gets the parameter value associated with address for the voice.
         * getVoiceParamValue can only be used if the [style:poly] metadata
         * is used in the Faust code.
         */
        float getVoiceParamValue(const char* address, int voice)
        {
            assert(sizeof(int) == sizeof(MapUI*));
            return reinterpret_cast<MapUI*>(voice)->getParamValue(address);
        }
    
        /*
         * getParamAddress(id)
         * Returns the address of a parameter in function of its "id".
         */
        const char* getParamAddress(int id)
        {
            return fAPIUI.getParamAddress(id);
        }

        /*
         * propagateAcc(int acc, float v)
         * Propage accelerometer value to the curve conversion layer.
         */
        void propagateAcc(int acc, float v)
        {
            fAPIUI.propagateAcc(acc, v);
        }

        /*
         * setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change accelerometer curve mapping.
         */
        void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
        {
           fAPIUI.setAccConverter(p, acc, curve, amin, amid, amax);
        }

        /*
         * propagateGyr(int gyr, float v)
         * Propage gyroscope value to the curve conversion layer.
         */
        void propagateGyr(int gyr, float v)
        {
            fAPIUI.propagateGyr(gyr, v);
        }

        /*
         * setGyrConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change gyroscope curve mapping.
         */
        void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
        {
            fAPIUI.setGyrConverter(p, gyr, curve, amin, amid, amax);
        }

        float getCPULoad() { return fDriver->get_cpu_load(); }

        int getScreenColor()
        {
            return fAPIUI.getScreenColor();
        }

};

#endif // __faust_poly_engine__

//**************************************************************
// Android Audio
//**************************************************************

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2015-2015 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 
 ************************************************************************
 *************************************************************************/

#ifndef __android_dsp__
#define __android_dsp__

#include <android/log.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <time.h>


#define CONV16BIT 32767.f
#define CONVMYFLT (1.f/32767.f)

#define NUM_INPUTS 2
#define NUM_OUTPUTS 2
#define CPU_TABLE_SIZE 16

struct CircularBuffer {
    
    short* fBuffer;
    int fReadIndex;
    int fWriteIndex;
    int fSize;
    int fChan;
    
    CircularBuffer(int frames, int chan)
    {
        fBuffer = new short[frames * chan];
        memset(fBuffer, 0, sizeof(short) * frames * chan);
        fSize = frames;
        fChan = chan;
        fReadIndex = 0;
        fWriteIndex = frames/2; // Set write index in the middle
    }
    
    ~CircularBuffer()
    {
        delete [] fBuffer;
    }
    
    short* getWritePtr() { return &fBuffer[fWriteIndex * fChan]; }
    short* getReadPtr() { return &fBuffer[fReadIndex * fChan]; }
    
    void moveWritePtr(int frames)
    {
        //__android_log_print(ANDROID_LOG_ERROR, "Faust", "moveWritePtr %x fWriteIndex = %ld", this, fWriteIndex);
        fWriteIndex = (fWriteIndex + frames) % fSize;
    }
    void moveReadPtr(int frames)
    {
        //__android_log_print(ANDROID_LOG_ERROR, "Faust", "moveReadPtr %x fReadIndex = %ld", this,  fReadIndex);
        fReadIndex = (fReadIndex + frames) % fSize;
    }
    
};

//http://stackoverflow.com/questions/17188761/how-to-obtain-computation-time-in-ndk

class androidaudio : public audio {
    
    protected:
    
        dsp* fDsp;
        
        int	fNumInChans;
        int	fNumOutChans;
        
        unsigned int fSampleRate;
        unsigned int fBufferSize;
    
        int64_t fCPUTable[CPU_TABLE_SIZE];
        int fCPUTableIndex;
    
        float** fInputs;
        float** fOutputs;
    
        CircularBuffer fOpenSLInputs;
        CircularBuffer fOpenSLOutputs;
    
        SLObjectItf fOpenSLEngine, fOutputMix, fInputBufferQueue, fOutputBufferQueue;
        SLAndroidSimpleBufferQueueItf fOutputBufferQueueInterface, fInputBufferQueueInterface;
    
        SLRecordItf fRecordInterface;
        SLPlayItf fPlayInterface;
    
        int64_t getTimeUsec() 
        {
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            return ((int64_t) now.tv_sec * 1000000000LL + now.tv_nsec)/1000;
        }
    
        void processAudio()
        {
            int64_t t1 = getTimeUsec();
       
            // Converting short input to float
            if (fNumInChans > 0) {
                short* input = fOpenSLInputs.getReadPtr();
                for (int chan = 0; chan < NUM_INPUTS; chan++) {
                    for (int i  = 0; i < fBufferSize; i++) {
                        fInputs[chan][i] = float(input[i * NUM_INPUTS + chan] * CONVMYFLT);
                    }
                }
                fOpenSLInputs.moveReadPtr(fBufferSize);
            }
            
            // Compute DSP
            fDsp->compute(fBufferSize, fInputs, fOutputs);
            
            // Converting float to short output
            if (fNumOutChans > 0) {
                short* output = fOpenSLOutputs.getWritePtr();
                for (int chan = 0; chan < NUM_OUTPUTS; chan++) {
                    for (int i = 0; i < fBufferSize; i++) {
                        output[i * NUM_OUTPUTS + chan] = short(min(1.f, max(-1.f, fOutputs[chan][i])) * CONV16BIT);
                    }
                }
                fOpenSLOutputs.moveWritePtr(fBufferSize);
            }
            
            int64_t t2 = getTimeUsec();
            fCPUTable[(fCPUTableIndex++)&(CPU_TABLE_SIZE-1)] = t2 - t1;
        }
    
        static void inputCallback(SLAndroidSimpleBufferQueueItf caller, void* arg)
        {
            androidaudio* obj = (androidaudio*)arg;
            obj->inputCallback(caller);
        }
    
        void inputCallback(SLAndroidSimpleBufferQueueItf caller)
        {
            SLresult result = (*caller)->Enqueue(caller, fOpenSLInputs.getWritePtr(), fBufferSize * sizeof(short) * NUM_INPUTS);
            fOpenSLInputs.moveWritePtr(fBufferSize);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "inputCallback Enqueue error = %d", int(result));
            }
        }
    
        static void outputCallback(SLAndroidSimpleBufferQueueItf caller, void* arg)
        {
            androidaudio* obj = (androidaudio*)arg;
            obj->outputCallback(caller);
        }
    
        void outputCallback(SLAndroidSimpleBufferQueueItf caller)
        {
            // Output callback drives DSP computation
            processAudio();
            
            SLresult result = (*caller)->Enqueue(caller, fOpenSLOutputs.getReadPtr(), fBufferSize * sizeof(short) * NUM_OUTPUTS);
            fOpenSLOutputs.moveReadPtr(fBufferSize);
            if (result != SL_RESULT_SUCCESS) {
                __android_log_print(ANDROID_LOG_ERROR, "Faust", "outputCallback Enqueue error = %d", int(result));
            }
        }
          
    public:
    
        androidaudio(long srate, long bsize)
        : fDsp(0), fSampleRate(srate),
        fBufferSize(bsize), fCPUTableIndex(0), fNumInChans(0), fNumOutChans(0),
        fOpenSLEngine(0), fOutputMix(0), fInputBufferQueue(0), fOutputBufferQueue(0),
        fOpenSLInputs(bsize * 4, NUM_INPUTS), fOpenSLOutputs(bsize * 4, NUM_OUTPUTS)
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "Constructor");
            
            // Allocating memory for input channels.
            fInputs = new float*[NUM_INPUTS];
            for (int i = 0; i < NUM_INPUTS; i++) {
                fInputs[i] = new float[fBufferSize];
                memset(fInputs[i], 0, fBufferSize * sizeof(float));
            }
    
            // Allocating memory for output channels.
            fOutputs = new float*[NUM_OUTPUTS];
            for (int i = 0; i < NUM_OUTPUTS; i++) {
                fOutputs[i] = new float[fBufferSize];
                memset(fOutputs[i], 0, fBufferSize * sizeof(float));
            }
        }

        virtual ~androidaudio()
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "Destructor");
            
            if (fInputBufferQueue) {
                (*fInputBufferQueue)->Destroy(fInputBufferQueue);
                fInputBufferQueue = NULL;
            }
            
            if (fOutputBufferQueue) {
                (*fOutputBufferQueue)->Destroy(fOutputBufferQueue);
                fOutputBufferQueue = NULL;
            }
            
            if (fOutputMix) {
                (*fOutputMix)->Destroy(fOutputMix);
                fOutputMix = NULL;
            }
             
            if (fOpenSLEngine) {
                (*fOpenSLEngine)->Destroy(fOpenSLEngine);
                fOpenSLEngine = NULL;
            }
            
            for (int i = 0; i < NUM_INPUTS; i++) {
                delete [] fInputs[i];
            }
            delete [] fInputs;
           
            for (int i = 0; i < NUM_OUTPUTS; i++) {
                delete [] fOutputs[i];
            }
            delete [] fOutputs;
        }
    
        // DSP CPU load in percentage of the buffer size duration
        float getCPULoad()
        {
            float sum = 0.f;
            for (int i = 0; i < CPU_TABLE_SIZE; i++) {
                sum += fCPUTable[i];
            }
            return (sum/float(CPU_TABLE_SIZE))/(10000.f*float(fBufferSize)/float(fSampleRate));
        }
    
        virtual bool init(const char* name, dsp* DSP)
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "init");
            
            fDsp = DSP;
            fNumInChans = fDsp->getNumInputs();
            fNumOutChans = fDsp->getNumOutputs();
            fDsp->init(fSampleRate);
            
            static const SLboolean requireds[2] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
            SLresult result;
            SLuint32 sr;
            
            switch (fSampleRate) {
                    
                case 8000:
                    sr = SL_SAMPLINGRATE_8;
                    break;
                case 11025:
                    sr = SL_SAMPLINGRATE_11_025;
                    break;
                case 16000:
                    sr = SL_SAMPLINGRATE_16;
                    break;
                case 22050:
                    sr = SL_SAMPLINGRATE_22_05;
                    break;
                case 24000:
                    sr = SL_SAMPLINGRATE_24;
                    break;
                case 32000:
                    sr = SL_SAMPLINGRATE_32;
                    break;
                case 44100:
                    sr = SL_SAMPLINGRATE_44_1;
                    break;
                case 48000:
                    sr = SL_SAMPLINGRATE_48;
                    break;
                case 64000:
                    sr = SL_SAMPLINGRATE_64;
                    break;
                case 88200:
                    sr = SL_SAMPLINGRATE_88_2;
                    break;
                case 96000:
                    sr = SL_SAMPLINGRATE_96;
                    break;
                case 192000:
                    sr = SL_SAMPLINGRATE_192;
                    break;
                default:
                    return false;
            }
          
            // Create the OpenSL ES engine.
            result = slCreateEngine(&fOpenSLEngine, 0, NULL, 0, NULL, NULL);
            if (result != SL_RESULT_SUCCESS) return false;
            
            result = (*fOpenSLEngine)->Realize(fOpenSLEngine, SL_BOOLEAN_FALSE);
            if (result != SL_RESULT_SUCCESS) return false;
            
            SLEngineItf openSLEngineInterface = NULL;
            result = (*fOpenSLEngine)->GetInterface(fOpenSLEngine, SL_IID_ENGINE, &openSLEngineInterface);
            if (result != SL_RESULT_SUCCESS) return false;
            
            // Create the output mix.
            result = (*openSLEngineInterface)->CreateOutputMix(openSLEngineInterface, &fOutputMix, 0, NULL, NULL);
            if (result != SL_RESULT_SUCCESS) return false;
            
            result = (*fOutputMix)->Realize(fOutputMix, SL_BOOLEAN_FALSE);
            if (result != SL_RESULT_SUCCESS) return false;
            
            SLDataLocator_OutputMix outputMixLocator = { SL_DATALOCATOR_OUTPUTMIX, fOutputMix };
            
            if (fNumInChans > 0) {
                // Create the input buffer queue.
                SLDataLocator_IODevice deviceInputLocator = { SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT, SL_DEFAULTDEVICEID_AUDIOINPUT, NULL };
                SLDataSource inputSource = { &deviceInputLocator, NULL };
                SLDataLocator_AndroidSimpleBufferQueue inputLocator = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 1 };
                SLDataFormat_PCM inputFormat = { SL_DATAFORMAT_PCM, 2, sr, SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16, SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN };
                SLDataSink inputSink = { &inputLocator, &inputFormat };
                const SLInterfaceID inputInterfaces[2] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE, SL_IID_ANDROIDCONFIGURATION };
                
                result = (*openSLEngineInterface)->CreateAudioRecorder(openSLEngineInterface, &fInputBufferQueue, &inputSource, &inputSink, 2, inputInterfaces, requireds);
                if (result != SL_RESULT_SUCCESS) return false;
                
            #if DISABLE_AGC
                SLAndroidConfigurationItf configObject;
                result = (*fInputBufferQueue)->GetInterface(fInputBufferQueue, SL_IID_ANDROIDCONFIGURATION, &configObject);
                if (result == SL_RESULT_SUCCESS) {
                    //SLuint32 mode = SL_ANDROID_RECORDING_PRESET_GENERIC;
                    SLuint32 mode = SL_ANDROID_RECORDING_PRESET_VOICE_RECOGNITION;
                    result = (*configObject)->SetConfiguration(configObject, SL_ANDROID_KEY_RECORDING_PRESET, &mode, sizeof(mode));
                    if (result != SL_RESULT_SUCCESS) {
                       __android_log_print(ANDROID_LOG_ERROR, "Faust", "SetConfiguration SL_ANDROID_KEY_RECORDING_PRESET error %d", result);
                    }
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, "Faust", "GetInterface SL_IID_ANDROIDCONFIGURATION error %d", result);
                }
            #endif
                
                result = (*fInputBufferQueue)->Realize(fInputBufferQueue, SL_BOOLEAN_FALSE);
                if (result != SL_RESULT_SUCCESS) return false;
            }
            
            if (fNumOutChans > 0) {
                // Create the output buffer queue.
                SLDataLocator_AndroidSimpleBufferQueue outputLocator = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 1 };
                SLDataFormat_PCM outputFormat = { SL_DATAFORMAT_PCM, 2, sr, SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16, SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN };
                SLDataSource outputSource = { &outputLocator, &outputFormat };
                const SLInterfaceID outputInterfaces[1] = { SL_IID_BUFFERQUEUE };
                SLDataSink outputSink = { &outputMixLocator, NULL };
                
                result = (*openSLEngineInterface)->CreateAudioPlayer(openSLEngineInterface, &fOutputBufferQueue, &outputSource, &outputSink, 1, outputInterfaces, requireds);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fOutputBufferQueue)->Realize(fOutputBufferQueue, SL_BOOLEAN_FALSE);
                if (result != SL_RESULT_SUCCESS) return false;
            }
            
            if (fNumInChans > 0) { // Initialize
                
                result = (*fInputBufferQueue)->GetInterface(fInputBufferQueue, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &fInputBufferQueueInterface);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fInputBufferQueueInterface)->RegisterCallback(fInputBufferQueueInterface, inputCallback, this);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fInputBufferQueue)->GetInterface(fInputBufferQueue, SL_IID_RECORD, &fRecordInterface);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fInputBufferQueueInterface)->Enqueue(fInputBufferQueueInterface,
                                                                fOpenSLInputs.getWritePtr(),
                                                                fBufferSize * sizeof(short) * NUM_INPUTS);
                fOpenSLInputs.moveWritePtr(fBufferSize);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fRecordInterface)->SetRecordState(fRecordInterface, SL_RECORDSTATE_STOPPED);
                if (result != SL_RESULT_SUCCESS) __android_log_print(ANDROID_LOG_ERROR, "Faust", "stop: SetRecordState error");
            }
            
            if (fNumOutChans > 0) { // Initialize
              
                result = (*fOutputBufferQueue)->GetInterface(fOutputBufferQueue, SL_IID_BUFFERQUEUE, &fOutputBufferQueueInterface);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fOutputBufferQueueInterface)->RegisterCallback(fOutputBufferQueueInterface, outputCallback, this);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fOutputBufferQueue)->GetInterface(fOutputBufferQueue, SL_IID_PLAY, &fPlayInterface);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fOutputBufferQueueInterface)->Enqueue(fOutputBufferQueueInterface,
                                                                 fOpenSLOutputs.getReadPtr(),
                                                                 fBufferSize * sizeof(short) * NUM_OUTPUTS);
                fOpenSLOutputs.moveReadPtr(fBufferSize);
                if (result != SL_RESULT_SUCCESS) return false;
                
                result = (*fPlayInterface)->SetPlayState(fPlayInterface, SL_PLAYSTATE_STOPPED);
                if (result != SL_RESULT_SUCCESS) __android_log_print(ANDROID_LOG_ERROR, "Faust", "stop: SetPlayState error");
            }
            
            return true;
        }
    
        virtual bool start()
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "start");
            SLresult result;
            
            if (fNumInChans > 0) {
                // start the inout buffer queue.
                result = (*fRecordInterface)->SetRecordState(fRecordInterface, SL_RECORDSTATE_RECORDING);
                if (result != SL_RESULT_SUCCESS) return false;
            }
            
            if (fNumOutChans > 0) {
                // start the output buffer queue.
                result = (*fPlayInterface)->SetPlayState(fPlayInterface, SL_PLAYSTATE_PLAYING);
                if (result != SL_RESULT_SUCCESS) return false;
            }
            
            return true;
        }
        
        virtual void stop()
        {
            __android_log_print(ANDROID_LOG_ERROR, "Faust", "stop");
            SLresult result;
            
            if (fNumInChans > 0) {
                result = (*fRecordInterface)->SetRecordState(fRecordInterface, SL_RECORDSTATE_PAUSED);
                if (result != SL_RESULT_SUCCESS) __android_log_print(ANDROID_LOG_ERROR, "Faust", "stop: SetRecordState error");
            }
            
            if (fNumOutChans > 0) {
                result = (*fPlayInterface)->SetPlayState(fPlayInterface, SL_PLAYSTATE_PAUSED);
                if (result != SL_RESULT_SUCCESS) __android_log_print(ANDROID_LOG_ERROR, "Faust", "stop: SetPlayState error");
            }
        }
    
        virtual int get_buffer_size()
        {
            return fBufferSize;
        }
        
        virtual int get_sample_rate()
        {
            return fSampleRate;
        }
        
        virtual int get_num_inputs()
        {
            return fNumInChans;
        }
        
        virtual int get_num_outputs()
        {
            return fNumOutChans;
        }
    
};

#endif 

//**************************************************************
// Native Faust API
//**************************************************************

#include <android/log.h>
#include "dsp_faust.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

class AndroidEngine : public FaustPolyEngine {

    protected:
    
        midi_handler fMidiHandler;
        MidiUI fMidiUI;

    public:

        AndroidEngine(int srate, int bsize):FaustPolyEngine(), fMidiUI(&fMidiHandler)
        {
            fDriver = new androidaudio(srate, bsize);
            fFinalDSP->buildUserInterface(&fMidiUI);
        }

        virtual ~AndroidEngine()
        {}

        // Allows to retrieve MIDI events in JAVA and to propagate to the Faust object.
        void propagateMidi(int count, double time, int type, int channel, int data1, int data2)
        {
            if (count == 3) fMidiHandler.handleData2(time, type, channel, data1, data2);
            else if (count == 2) fMidiHandler.handleData1(time, type, channel, data1);
            else if (count == 1) fMidiHandler.handleSync(time, type);
			GUI::updateAllGuis();
        }
};

static AndroidEngine* gGlobal = NULL;

/*
 * init(samplingRate, bufferFrames)
 * Initializes the Audio engine and the DSP code
 * with samplingRate and bufferFrames.
 * This method also looks for the [style:poly]
 * metadata in the Faust code and initializes a
 * polyphonic object or not based on that. init
 * should be called before start.
 */
bool init(int sample_rate, int buffer_size)
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI init");
    gGlobal = new AndroidEngine(sample_rate, buffer_size);
    return gGlobal->init();
}

/*
 * start()
 * Begins the processing and return 1 if the connection
 * with the audio device was successful and 0 if not.
 * On Android it also creates the native thread where the
 * DSP tasks will be computed.
 */
bool start()
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI start");
    return gGlobal->start();
}

/*
 * stop()
 * Stops the processing.
 */
void stop()
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI stop");
	 return gGlobal->stop();
}

/*
 * destroy()
 * Destroy the audio engine and related ressources.
 * the native thread on Android.
 */
void destroy()
{
    __android_log_print(ANDROID_LOG_ERROR, "Faust", "JNI destroy");
    delete gGlobal;
    gGlobal = NULL;
}

/*
 * isRunning()
 * returns true if the DSP frames are being computed and
 * false if not.
 */
bool isRunning()
{
	return (gGlobal != NULL);
}

/*
 * keyOn(pitch, velocity)
 * Instantiates a new polyphonic voice where velocity
 * and pitch are MIDI numbers (0-127). keyOn can only
 * be used if the [style:poly] metadata is used in the
 * Faust code. keyOn will return 0 if the object is not
 * polyphonic and 1 otherwise.
 */
int keyOn(int pitch, int velocity)
{
    if(gGlobal->keyOn(pitch, velocity) != NULL){
		return 1;
	}
	else return 0;
}

/*
 * keyOff(pitch)
 * De-instantiates a polyphonic voice where pitch is the
 * MIDI number of the note (0-127). keyOff can only be
 * used if the [style:poly] metadata is used in the Faust
 * code. keyOn will return 0 if the object is not polyphonic
 * and 1 otherwise.
 */
int keyOff(int pitch)
{
	return gGlobal->keyOff(pitch);
}

/*
 * getJSON()
 * Returns a string containing a JSON description of the
 * UI of the Faust object.
 */
const char* getJSON()
{
    return gGlobal->getJSON();
}

/*
 * getParamsCount()
 * Returns the number of control parameters of the Faust object.
 */
int getParamsCount()
{
    return gGlobal->getParamsCount();
}

/*
 * getParam(address)
 * Takes the address of a parameter and returns its current
 * value.
 */
float getParamValue(const char* address)
{
    return gGlobal->getParamValue(address);
}

/*
 * setParam(address, value)
 * Sets the value of the parameter associated with address.
 */
void setParamValue(const char* address, float value)
{
    return gGlobal->setParamValue(address, value);
}

/*
 * setVoiceParamValue(address, voice, value)
 * Sets the value of the parameter associated with address for
 * the voice. setVoiceParamValue can only be
 * used if the [style:poly] metadata is used in the Faust code.
 */
void setVoiceParamValue(const char* address, int voice, float value)
{
    gGlobal->setVoiceParamValue(address, voice, value);
}

/*
 * getVoiceParamValue(address, voice)
 * Gets the parameter value associated with address for the voice.
 * getVoiceParamValue can only be used if the [style:poly] metadata
 * is used in the Faust code.
 */
float getVoiceParamValue(const char* address, int voice)
{
    return gGlobal->getVoiceParamValue(address, voice);
}

/*
 * getParamAddress(id)
 * Returns the address of a parameter in function of its "id".
 */
const char* getParamAddress(int id)
{
    return gGlobal->getParamAddress(id);
}

/*
 * propagateAcc(int acc, float v)
 * Propage accelerometer value to the curve conversion layer.
 */
void propagateAcc(int acc, float v)
{
    // 05/23/26 : values have to be inverted to behave as with iOS implementation
    gGlobal->propagateAcc(acc, -v);
}

/*
 * setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
 * Change accelerometer curve mapping.
 */
void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
{
    //__android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter %d %d %d %f %f %f", p, acc, curve, amin, amid, amax);
    gGlobal->setAccConverter(p, acc, curve, amin, amid, amax);
}

/*
 * propagateGyr(int gyr, float v)
 * Propage gyroscope value to the curve conversion layer.
 */
void propagateGyr(int gyr, float v)
{
    gGlobal->propagateGyr(gyr, v);
}

/*
 * setGyrConverter(int p, int acc, int curve, float amin, float amid, float amax)
 * Change gyroscope curve mapping.
 */
void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
{
    //__android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter %d %d %d %f %f %f", p, acc, curve, amin, amid, amax);
    gGlobal->setGyrConverter(p, gyr, curve, amin, amid, amax);
}

/*
 * propagateMidi(double time, int type, int channel, int data1, int data2)
 * Allows to retrieve MIDI events in JAVA and to propagate to the Faust object.
 */
void propagateMidi(int count, double time, int type, int channel, int data1, int data2){
	gGlobal->propagateMidi(count, time, type, channel, data1, data2);
}

/*
 * getCPULoad()
 * Return DSP CPU load.
 */
float getCPULoad()
{
    return gGlobal->getCPULoad();
}

 /*
 * getScreenColor() -> c:int
 * Get the requested screen color c :
 * c <  0 : no screen color requested (keep regular UI)
 * c >= 0 : requested color (no UI but a colored screen)
 */
 int getScreenColor()
 {
     //__android_log_print(ANDROID_LOG_ERROR, "Faust", "setAccConverter %d %d %d %f %f %f", p, acc, curve, amin, amid, amax);
     return gGlobal->getScreenColor();
 }
