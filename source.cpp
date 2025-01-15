#include <vector>


// Implement a random engine
template <typename FloatType>
class UniformDistribution {
    std::random_device rd;
    std::default_random_engine eng;
    std::uniform_real_distribution<FloatType> dist;
public:
    UniformDistribution(FloatType minVal, FloatType maxVal): rd(), eng(rd()), dist(minVal, maxVal) {  }
    FloatType random() { return dist(eng); }
    template <typename IntType>
    IntType randint(IntType maxVal) { return std::min((IntType)(dist(eng) * maxVal), maxVal - 1); }
};

static UniformDistribution<float> uniform(0.f, 1.f);

// Blind Box
template <typename dtype>
class BlindBox {
    size_t Length;
    std::vector<dtype> data;
    UniformDistribution<float>& dist = uniform;
    size_t GetIndex() const {
        return dist.randint(Length);
    }
public:

    BlindBox(const std::vector<dtype>& _init_Data = {}) : data(_init_Data) {
        Length = data.size();
    }

    const std::vector<dtype>& All() const { return data; }
    size_t size() const { return Length; }

    void Push(const dtype& _elem) {
        data.push_back(_elem);
        Length++;
    }
    const dtype& Get() const {
        if (Length == 0) {
            std::cerr << "Cannot get an element from an empty Box" << std::endl;
            throw 0; // or anything you like
        }
        return data[GetIndex()];
    }
    dtype Pop() {
        if (Length == 0) {
            std::cerr << "Cannot get an element from an empty Box" << std::endl;
            throw 0;
        }
        std::swap(data[GetIndex()], data[Length - 1]);
        dtype ret = data[Length - 1];
        data.pop_back();
        --Length;
        return std::move(ret);
    }

    bool Empty() const {
        return Length == 0;
    }
};
