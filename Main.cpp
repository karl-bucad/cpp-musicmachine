// Programming assignment MusicMachine.
// Macomb Community College
// Karl Bucad

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace MusicMachine {
    // Enum representing different types of music
    enum class MUSIC_TYPE { CHAMBER, ORCHESTRAL, POP, JAZZ, ROCK, ELECTRONIC };

    // Base class representing a generic music piece
    class Music {
    protected:
        string title; // Title of the music
        MUSIC_TYPE type; // Type of music
    public:
        Music(string t, MUSIC_TYPE mt) : title(t), type(mt) {}
        virtual ~Music() {} // Virtual destructor for proper polymorphic behavior
        virtual void Play() const = 0; // Pure virtual function to enforce implementation in derived classes
        virtual bool operator==(const Music& other) const { return title == other.title && type == other.type; }
        MUSIC_TYPE GetMusicType() const { return type; }
        friend ostream& operator<<(ostream& os, const Music& m) {
            os << "Playing: " << m.title;
            return os;
        }
    };

    // Chamber music class, derived from Music
    class Chamber : public Music {
    private:
        string key;
        vector<string> keys = { "A", "B", "C", "D", "E", "F", "G" }; // List of valid keys
        int keyIndex; // Index of the current key
    public:
        Chamber(string t, string k) : Music(t, MUSIC_TYPE::CHAMBER), key(k) {
            // Find the index of the given key, default to 0 if not found
            auto it = find(keys.begin(), keys.end(), key);
            keyIndex = (it != keys.end()) ? distance(keys.begin(), it) : 0;
        }

        void Play() const override { cout << "Chamber music in " << key << " key." << endl; }
        string GetKey() const { return key; }

        // Prefix incrememnt operator: moves to the next key in the cycle
        Chamber& operator++() {
            keyIndex = (keyIndex + 1) % keys.size();
            key = keys[keyIndex];
            return *this;
        }

        // Postfix increment operator: moves to the next key, but returns the previous state
        Chamber operator++(int) {
            Chamber temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Chamber& other) const { return Music::operator==(other) && key == other.key; }
    };

    // Orchestral music class, derived from Music
    class Orchestral : public Music {
    public:
        Orchestral(string t) : Music(t, MUSIC_TYPE::ORCHESTRAL) {}
        void Play() const override { cout << "Orchestral music playing." << endl; }
        bool operator==(const Orchestral& other) const { return Music::operator==(other); }
    };

    // Pop music class, derived from Music
    class Pop : public Music {
    public:
        Pop(string t) : Music(t, MUSIC_TYPE::POP) {}
        void Play() const override { cout << "Pop music playing." << endl; }
        bool operator==(const Pop& other) const { return Music::operator==(other); }
        bool operator<(const Pop&) const { return false; }
        bool operator>(const Pop&) const { return false; }
    };

    // Jazz music class, derived from Music
    class Jazz : public Music {
    public:
        Jazz(string t) : Music(t, MUSIC_TYPE::JAZZ) {}
        void Play() const override { cout << "Jazz music playing." << endl; }
        bool operator==(const Jazz& other) const { return Music::operator==(other); }
    };

    // Rock music class, derived from Music
    class Rock : public Music {
    private:
        bool loud; // Determines whether the music is loud
    public:
        Rock(string t, bool isLoud) : Music(t, MUSIC_TYPE::ROCK), loud(isLoud) {}

        void Play() const override { cout << "Rock music blasting." << endl; }

        bool IsLoud() const { return loud; }
        bool IsVeryLoud() const { return loud; }
        bool IsQuite() const { return loud; }

        // Prefix increment toggles loudness
        Rock& operator++() {
            loud = !loud;
            return *this;
        }

        // Postfix increment toggles loudness and returns the previous state
        Rock operator++(int) {
            Rock temp = *this;  // Copy current state
            temp.loud = !temp.loud;  // Toggle loudness in the copy
            return temp;  // Return modified copy
        }

        bool operator==(const Rock& other) const {
            return Music::operator==(other) && loud == other.loud;
        }
    };

    // Electronic music class, derived from Music
    class Electronic : public Music {
    private:
        int bpm; // Beats per minute
    public:
        Electronic(string t, int b) : Music(t, MUSIC_TYPE::ELECTRONIC), bpm(b) {}
        void Play() const override { cout << "Electronic beats at " << bpm << " BPM." << endl; }
        int GetBeatsPerMinute() const { return bpm; }
        Electronic& operator++() { bpm++; return *this; }
        Electronic& operator--() { bpm--; return *this; }
        bool operator==(const Electronic& other) const { return Music::operator==(other) && bpm == other.bpm; }
    };

    // Music Machien that stores and manages different types of music
    class Machine {
    private:
        vector<Music*> playlist; // Stores dynamically allocated music objects
    public:
        Machine() {
            // Populate playlist with different music types
            playlist.push_back(new Chamber("Symphony No. 5", "G"));
            playlist.push_back(new Orchestral("Beethoven's 9th"));
            playlist.push_back(new Pop("Thriller"));
            playlist.push_back(new Jazz("Take Five"));
            playlist.push_back(new Rock("Bohemian Rhapsody", true));
            playlist.push_back(new Electronic("Sandstorm", 141));
        }
        // Delets all dynamically allocated memory
        ~Machine() { for (auto song : playlist) delete song; }
        int Parse() const { return playlist.size(); }
        int GetSongCount() const { return playlist.size(); }
        Music& operator[](int i) { return *playlist[i % playlist.size()]; }
    };
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <crtdbg.h>
TEST_CASE("Testing my Music Machine")
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SUBCASE("testing the parsing of file - JsonObject8a.json")
    {
        const int MAX_SONGS = 10;
        MusicMachine::Machine m;

        const int MAX_RECORDS = 6;

        // Invoke the parsing process
        CHECK(m.Parse() == MAX_RECORDS);

        //
        const int iSongCount = m.GetSongCount();

        // Notice that the loop is done twice
        for (int i = 0; i < iSongCount * 2; i++)
        {
            // Virtual function of base class "plays" the correct instance of derived class.
            m[i].Play();
            cout << m[i] << endl;
            cout << endl;

            // Test the "==" operator the Music class...
            CHECK((m[i] == m[i]) == true);


            // Unit testing the derived classes...
            if (m[i].GetMusicType() == MusicMachine::MUSIC_TYPE::CHAMBER)
            {
                MusicMachine::Chamber& c = dynamic_cast<MusicMachine::Chamber&>(m[i]);
                CHECK((c == c) == true);
                CHECK((c).GetKey()   == "G");
                c++;
                CHECK((c).GetKey() == "A");
                c++;
                CHECK((c).GetKey() == "B");
                c++;
                CHECK((c).GetKey() == "C");
                c++;
                CHECK((c).GetKey() == "D");
                c++;
                CHECK((c).GetKey() == "E");
                c++;
                CHECK((c).GetKey() == "F");
                c++;
                CHECK((c).GetKey() == "G");
            }

            else if (m[i].GetMusicType() == MusicMachine::MUSIC_TYPE::ORCHESTRAL)
            {
                MusicMachine::Orchestral& o = dynamic_cast<MusicMachine::Orchestral&>(m[i]);
                CHECK((o == o) == true);
            }
            else if (m[i].GetMusicType() == MusicMachine::MUSIC_TYPE::POP)
            {
                MusicMachine::Pop& p = dynamic_cast<MusicMachine::Pop&>(m[i]);
                CHECK((p == p) == true);
                CHECK((p < p) == false);
                CHECK((p > p) == false);
            }
            else if (m[i].GetMusicType() == MusicMachine::MUSIC_TYPE::JAZZ)
            {
                MusicMachine::Jazz& j = dynamic_cast<MusicMachine::Jazz&>(m[i]);
                CHECK((j == j) == true);
            }
            else if (m[i].GetMusicType() == MusicMachine::MUSIC_TYPE::ROCK)
            {
                MusicMachine::Rock& r = dynamic_cast<MusicMachine::Rock&>(m[i]);
                CHECK((r == r) == true);
                CHECK((r).IsLoud() == true);
                CHECK((r++).IsLoud() == false);
                CHECK((r).IsVeryLoud() == true);
                CHECK((r++).IsVeryLoud() == false);
                CHECK((r).IsQuite() == true);
                CHECK((r++).IsQuite() == false);
            }
            else if (m[i].GetMusicType() == MusicMachine::MUSIC_TYPE::ELECTRONIC)
            {
                MusicMachine::Electronic& e = dynamic_cast<MusicMachine::Electronic&>(m[i]);
                CHECK((e == e) == true);
                CHECK((e).GetBeatsPerMinute() == 141);
                CHECK((++e).GetBeatsPerMinute() == 142);
                CHECK((--e).GetBeatsPerMinute() == 141);
            }
        }
    }
}
