// SINGLETON
class audio_mixer {
private:

public:
/* singleton */
    static
    audio_mixer& get()
    {
        static audio_mixer Mixer;
        return Mixer;
    }
private:
/* singleton */
    audio_mixer(){}
};
