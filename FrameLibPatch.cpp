
#include "FrameLibPatch.h"
#include "FrameLib_Objects.h"

FrameLibPatch::FrameLibPatch(FrameLib_Proxy *proxy) : mNumAudioIns(0), mNumAudioOuts(0), mProxy(proxy)
{
    using Connection = FrameLib_Object<FrameLib_Multistream>::Connection;

    FrameLib_Global::get(&mGlobal);
    FrameLib_Context context(mGlobal, this);
    FrameLib_Parameters::AutoSerial parameters;

    mObjects.resize(37);

    parameters.clear();
    mObjects[0] = new FrameLib_Expand<FrameLib_PerBlock>(context, &parameters, mProxy, 1);

    parameters.clear();
    mObjects[1] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[1]->addConnection(Connection(mObjects[0], 0), 0);

    double fl_2_vector_1[] = { 0 };
    double fl_2_vector_2[] = { 1 };
    double fl_2_vector_3[] = { 30 };
    double fl_2_vector_4[] = { 70 };
    parameters.clear();
    parameters.write("mode", "linear");
    parameters.write("inlo", fl_2_vector_1, 1);
    parameters.write("inhi", fl_2_vector_2, 1);
    parameters.write("outlo", fl_2_vector_3, 1);
    parameters.write("outhi", fl_2_vector_4, 1);
    mObjects[2] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[2]->addConnection(Connection(mObjects[1], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "interval");
    mObjects[3] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[3]->addConnection(Connection(mObjects[2], 0), 0);

    double fl_4_vector_0[] = { 100 };
    parameters.clear();
    parameters.write("interval", fl_4_vector_0, 1);
    parameters.write("units", "ms");
    mObjects[4] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);
    mObjects[4]->addConnection(Connection(mObjects[3], 0), 0);

    parameters.clear();
    mObjects[5] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[5]->addConnection(Connection(mObjects[0], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "interval");
    mObjects[6] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[6]->addConnection(Connection(mObjects[5], 0), 0);

    parameters.clear();
    parameters.write("units", "ms");
    mObjects[7] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);
    mObjects[7]->addConnection(Connection(mObjects[6], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "length");
    mObjects[8] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[8]->addConnection(Connection(mObjects[5], 0), 0);

    double fl_9_vector_0[] = { 5000 };
    parameters.clear();
    parameters.write("buffer_size", fl_9_vector_0, 1);
    parameters.write("units", "ms");
    mObjects[9] = new FrameLib_Expand<FrameLib_Source>(context, &parameters, mProxy, 1);
    mObjects[9]->addConnection(Connection(mObjects[7], 0), 0);
    mObjects[9]->addConnection(Connection(mObjects[8], 0), 1);

    parameters.clear();
    parameters.write("name", "fb");
    mObjects[10] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[10]->addConnection(Connection(mObjects[9], 0), 0);

    parameters.clear();
    parameters.write("mismatch", "pad_in");
    mObjects[11] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::plus<double> > >(context, &parameters, mProxy, 1);
    mObjects[11]->addConnection(Connection(mObjects[9], 0), 0);
    mObjects[11]->addConnection(Connection(mObjects[10], 0), 1);

    parameters.clear();
    parameters.write("name", "fb");
    mObjects[12] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[12]->addConnection(Connection(mObjects[11], 0), 0);

    parameters.clear();
    parameters.write("name", "fb");
    mObjects[13] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[13]->addConnection(Connection(mObjects[4], 0), 0);
    mObjects[13]->addOrderingConnection(Connection(mObjects[12], 0));

    parameters.clear();
    mObjects[14] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[14]->addConnection(Connection(mObjects[13], 0), 0);

    parameters.clear();
    mObjects[15] = new FrameLib_Expand<FrameLib_TernaryOp<Ternary_Functor<&FrameLib_Ternary_Ops::clip<double>> > >(context, &parameters, mProxy, 1);
    double fl_15_inputs_1[] = { 0 };
    double fl_15_inputs_2[] = { 1 };
    mObjects[15]->setFixedInput(1, fl_15_inputs_1 , 1);
    mObjects[15]->setFixedInput(2, fl_15_inputs_2 , 1);
    mObjects[15]->addConnection(Connection(mObjects[14], 0), 0);

    parameters.clear();
    mObjects[16] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[16]->addConnection(Connection(mObjects[13], 0), 0);

    parameters.clear();
    mObjects[17] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::less_equal<double> > >(context, &parameters, mProxy, 1);
    mObjects[17]->addConnection(Connection(mObjects[16], 0), 0);
    mObjects[17]->addConnection(Connection(mObjects[15], 0), 1);

    parameters.clear();
    mObjects[18] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::plus<double> > >(context, &parameters, mProxy, 1);
    double fl_18_inputs_1[] = { 1 };
    mObjects[18]->setFixedInput(1, fl_18_inputs_1 , 1);
    mObjects[18]->addConnection(Connection(mObjects[17], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[19] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[19]->addConnection(Connection(mObjects[18], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "output");
    mObjects[20] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[20]->addConnection(Connection(mObjects[18], 0), 0);

    parameters.clear();
    mObjects[21] = new FrameLib_Expand<FrameLib_Route>(context, &parameters, mProxy, 1);
    mObjects[21]->addConnection(Connection(mObjects[13], 0), 0);
    mObjects[21]->addConnection(Connection(mObjects[20], 0), 1);

    parameters.clear();
    mObjects[22] = new FrameLib_Expand<FrameLib_Reverse>(context, &parameters, mProxy, 1);
    mObjects[22]->addConnection(Connection(mObjects[21], 1), 0);

    parameters.clear();
    mObjects[23] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[23]->addConnection(Connection(mObjects[21], 0), 0);
    mObjects[23]->addConnection(Connection(mObjects[22], 0), 1);
    mObjects[23]->addConnection(Connection(mObjects[19], 0), 2);

    parameters.clear();
    mObjects[24] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[24]->addConnection(Connection(mObjects[4], 0), 0);

    parameters.clear();
    mObjects[25] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[25]->addConnection(Connection(mObjects[23], 0), 0);
    mObjects[25]->addConnection(Connection(mObjects[24], 0), 1);

    parameters.clear();
    mObjects[26] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, true> >(context, &parameters, mProxy, 1);
    mObjects[26]->addConnection(Connection(mObjects[25], 0), 0);

    double fl_27_vector_0[] = { 1 };
    parameters.clear();
    parameters.write("mode", fl_27_vector_0, 1);
    mObjects[27] = new FrameLib_Expand<FrameLib_Pattern>(context, &parameters, mProxy, 1);
    double fl_27_inputs_1[] = { 1, 0.500000, 0.250000 };
    mObjects[27]->setFixedInput(1, fl_27_inputs_1 , 3);
    mObjects[27]->addConnection(Connection(mObjects[26], 0), 0);

    parameters.clear();
    mObjects[28] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[28]->addConnection(Connection(mObjects[26], 0), 0);
    mObjects[28]->addConnection(Connection(mObjects[27], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "length");
    mObjects[29] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[29]->addConnection(Connection(mObjects[28], 0), 0);

    parameters.clear();
    parameters.write("units", "samples");
    parameters.write("scale", "normalised");
    mObjects[30] = new FrameLib_Expand<FrameLib_Ramp>(context, &parameters, mProxy, 1);
    mObjects[30]->addConnection(Connection(mObjects[25], 0), 0);
    mObjects[30]->addConnection(Connection(mObjects[29], 0), 1);

    parameters.clear();
    parameters.write("trigger_ins", "left");
    mObjects[31] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[31]->addConnection(Connection(mObjects[30], 0), 0);
    mObjects[31]->addConnection(Connection(mObjects[26], 0), 1);

    parameters.clear();
    parameters.write("interp", "hermite");
    mObjects[32] = new FrameLib_Expand<FrameLib_Lookup>(context, &parameters, mProxy, 1);
    mObjects[32]->addConnection(Connection(mObjects[31], 0), 0);
    mObjects[32]->addConnection(Connection(mObjects[25], 0), 1);

    parameters.clear();
    parameters.write("window", "cosine");
    mObjects[33] = new FrameLib_Expand<FrameLib_Window>(context, &parameters, mProxy, 1);
    mObjects[33]->addConnection(Connection(mObjects[32], 0), 0);

    parameters.clear();
    mObjects[34] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    double fl_34_inputs_1[] = { 0.500000 };
    mObjects[34]->setFixedInput(1, fl_34_inputs_1 , 1);
    mObjects[34]->addConnection(Connection(mObjects[33], 0), 0);

    parameters.clear();
    mObjects[35] = new FrameLib_Expand<FrameLib_Sink>(context, &parameters, mProxy, 1);
    mObjects[35]->addConnection(Connection(mObjects[34], 0), 0);

    parameters.clear();
    parameters.write("name", "fb");
    mObjects[36] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[36]->addConnection(Connection(mObjects[25], 0), 0);

    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        if ((*it)->getType() == kScheduler || (*it)->getNumAudioChans())//if ((*it)->handlesAudio())
            mAudioObjects.push_back(*it);

        mNumAudioIns += (*it)->getNumAudioIns();
        mNumAudioOuts += (*it)->getNumAudioOuts();
    }
}

FrameLibPatch::~FrameLibPatch()
{
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
        delete *it;

    mObjects.clear();
    mAudioObjects.clear();
    delete mProxy;
    FrameLib_Global::release(&mGlobal);
}

void FrameLibPatch::reset(double samplerate, unsigned long maxvectorsize)
{
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
        (*it)->reset(samplerate, maxvectorsize);
}

void FrameLibPatch::process(double **inputs, double **outputs, unsigned long blockSize)
{
    for (auto it = mAudioObjects.begin(); it != mAudioObjects.end(); it++)
    {
        (*it)->blockUpdate(inputs, outputs, blockSize);

        inputs += (*it)->getNumAudioIns();
        outputs += (*it)->getNumAudioOuts();
    }
}