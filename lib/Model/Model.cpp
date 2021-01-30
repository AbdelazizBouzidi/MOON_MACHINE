#include <Model.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

ModelInit::ModelInit(int inputSize, int hiddenLayerSize, int outputSize, vector<double> W, vector<double> B)
{
    this->inputSize = inputSize;
    this->hiddenLayerSize = hiddenLayerSize;
    this->outputSize = outputSize;
    this->W.operator=(W);
    this->B.operator=(B);
    this->Z.assign(hiddenLayerSize, 0);
    this->outPuts.assign(outputSize, 0);
}
void ModelInit::init()
{
    this->Z.assign(hiddenLayerSize, 0);
    this->outPuts.assign(outputSize, 0);
    this->blastIndex = 0;
    this->wlastIndex = 0;
}
int ModelInit::predict(float R, float G, float B)
{
    std::vector<double> Colour = {R / (R + G + B),
                                  G / (R + G + B),
                                  B / (R + G + B)};
    this->init();
    this->feedForward(Colour, this->Z, false);
    this->feedForward(Colour, this->Z, true);
    this->relu(this->Z);
    this->feedForward(this->Z, this->outPuts, false);
    this->feedForward(this->Z, this->outPuts, true);
    this->softmax(this->outPuts);
    return this->max(this->outPuts);
}

void ModelInit::feedForward(vector<double> inp, vector<double> &Z, bool bias)
{
    if (bias == false)
    {
        int k = 0;
        for (int j = 0; j < inp.size(); j++)
        {
            for (int i = j * Z.size(); i < (j + 1) * Z.size(); i++)
            {
                k = k < Z.size() ? k : 0;
                Z[k] += this->W[this->wlastIndex + i] * inp[j];
                k++;
            }
        }
        this->wlastIndex = inp.size() * Z.size();
    }
    else
    {
        int k = 0;

        for (int i = this->blastIndex; i < this->blastIndex + Z.size(); i++)
        {
            k = k < Z.size() ? k : 0;
            Z[k] += this->B[i];
            k++;
        }
        this->blastIndex = Z.size();
    }
}
void ModelInit::relu(std::vector<double> &z)
{
    for (int i = 0; i < z.size(); i++)
    {
        z[i] = z[i] > 0 ? z[i] : 0;
        // Serial.println(z[i]);
    }
}
void ModelInit::softmax(std::vector<double> &z)
{
    float sum = 0;
    for (int i = 0; i < z.size(); i++)
    {
        sum += exp(z[i]);
    }
    for (int i = 0; i < z.size(); i++)
    {
        z[i] = exp(z[i]) / sum;
    }
}
int ModelInit::max(std::vector<double> z)
{
    int MAX = 0;
    for (int I = 0; I < z.size(); I++)
    {
        if (z[I] > z[MAX])
            MAX = I;
    }
    return MAX + 1;
}
