// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"


float calculate_semitone(float semitone);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int beat = atoi(&fraction[0]);
    int eighth = atoi(&fraction[2]);

    if (eighth == 8)
    {
        return beat;
    }
    else if (eighth == 4)
    {
        return beat * 2;
    }
    else if (eighth == 2)
    {
        return beat * 4;
    }
    else if (eighth == 1)
    {
        return beat * 8;
    }
    else
    {
        return false;
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int octave = atoi(&note[strlen(note) - 1]);

    float note_frequency = 0.0;

    float base_frequency = 440.0;

    char base_note = note[0];

    if (base_note == 'A')
    {
        note_frequency = base_frequency;
    }
    else if (base_note == 'B')
    {
        note_frequency = base_frequency * calculate_semitone(2.0);
    }
    else if (base_note == 'C')
    {
        note_frequency = base_frequency / calculate_semitone(9.0);
    }
    else if (base_note == 'D')
    {
        note_frequency = base_frequency / calculate_semitone(7.0);
    }
    else if (base_note == 'E')
    {
        note_frequency = base_frequency / calculate_semitone(5.0);
    }
    else if (base_note == 'F')
    {
        note_frequency = base_frequency / calculate_semitone(4.0);
    }
    else if (base_note == 'G')
    {
        note_frequency = base_frequency / calculate_semitone(2.0);
    }

    if (octave > 4)
    {
        for (int i = 0; i < octave - 4; i++)
        {
            note_frequency *= 2;
        }
    }
    else if (octave < 4)
    {
        for (int i = 0; i < 4 - octave; i++)
        {
            note_frequency /= 2;
        }
    }

    if (note[1] == '#')
    {
        note_frequency *= calculate_semitone(1.0);
    }
    else if (note[1] == 'b')
    {
        note_frequency /= calculate_semitone(1.0);
    }

    int rounded_freq = round(note_frequency);

    return rounded_freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }

    return false;
}

float calculate_semitone(float semitone)
{
    return (pow(2.0, (semitone / 12.0)));
}
