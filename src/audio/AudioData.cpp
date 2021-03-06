#include <audio/AudioData.h>
#include <iostream>
#include <AL/al.h>


using namespace std;

bool endWith(const string &a, const string &b) {
    int i = 0;
    int j = a.length() - b.length();
    if (j > 0) {
        for (; i < b.length() && j < a.length() && j > 0; i++, j++) {
            if (a[j] != b[i]) {
                return false;
            }
        }
    }
    return true;
}

const string &AudioData::get_name() const {
    return _name;
}

AudioData::~AudioData() {
    if (_source) {
        if (_bitsPerSample == 16) {
            delete[] (__int16_t *) _source;
        } else {
            delete[] (__int8_t *) _source;
        }

    }
}

AudioData *AudioData::load(const string &filename) {
    if (endWith(filename, ".wav")) {
        return load_wav(filename);
    } else if (endWith(filename, ".ogg")) {
        return load_ogg(filename);
    } else if (endWith(filename, ".mp3")) {
        return load_mp3(filename);
    } else {
        return NULL;
    }
}

AudioData *AudioData::load_mp3(const std::string &filename) {
    return NULL;
}

AudioData::AudioData(const string &name, ALvoid *source, ALsizei frames, size_t sampleRate, int channels,
                     int bitsPerSample) {
    this->_source = source;
    this->_name = name;
    this->_size = frames * channels * bitsPerSample / 8;
    this->_samples = frames;
//    this->_size = frames*channels;
    this->_sampleRate = sampleRate;
    this->_bitsPerSample = bitsPerSample;
    this->_channels = channels;
}

AudioData *AudioData::load_wav(const std::string &filename) {

    AudioData *sound = NULL;
    //try to open file
    SF_INFO info;
    SNDFILE *file = sf_open(filename.c_str(), SFM_READ, &info);
    if (file) {
        //switch file's format 16 or 8 bit and read raw rawBytes data
        if (SF_FORMAT_PCM_16 & info.format) {
            __int16_t *data = new __int16_t[info.frames * info.channels];
            sf_read_short(file, data, info.frames * info.channels);
            sound = new AudioData(filename, data, info.frames, info.samplerate, info.channels, 16);
        } else if (SF_FORMAT_PCM_S8 & info.format) {
            __int8_t *data = new __int8_t[info.frames * info.channels];
            sf_read_raw(file, data, info.frames * info.channels);
            sound = new AudioData(filename, data, info.frames, info.samplerate, info.channels, 8);
        }
    sf_close(file);
    }
    return sound;
}

AudioData *AudioData::load_ogg(const std::string &filename) {
    return NULL;
}

string AudioData::toString() {
    string s = "name: " + _name + "\n";
    s += "size in bytes: " + to_string(_size) + "\n";
    s += "frames: " + to_string(_samples) + "\n";
    s += "sample rate: " + to_string(_sampleRate) + "\n";
    s += "bits per sample: " + to_string(_bitsPerSample) + "\n";
    s += "channels: " + to_string(_channels);
    return s;
}

ALsizei AudioData::get_size() const {
    return _size;
}

ALint AudioData::get_sampleRate() const {
    return _sampleRate;
}

int AudioData::get_channels() const {
    return _channels;
}

int AudioData::get_bitsPerSample() const {
    return _bitsPerSample;
}

ALvoid *AudioData::get_source() const {
    return _source;
}

ALsizei AudioData::get_samples() const {
    return _samples;
}
