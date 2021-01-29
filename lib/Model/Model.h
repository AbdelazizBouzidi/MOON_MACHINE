#include <vector>
using namespace std;
class ModelInit
{

private:
    int inputSize;
    int hiddenLayerSize;
    int outputSize;
    int wlastIndex = 0;
    int blastIndex = 0;
    vector<double> outPuts;
    vector<double> W;
    vector<double> B;
    vector<double> Z;
    void feedForward(vector<double> inp, vector<double> &z, bool bias);
    void relu(vector<double> &z);
    void softmax(vector<double> &z);
    void init();
    int max(vector<double> z);

public:
    ModelInit(int inputSize, int hiddenLayerSize, int outputSize, vector<double> W, vector<double> B);
    int predict(float R, float G, float B);
};