#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "tourney_std.h"

int main(void)
{
    clearScreen();
    Participant *participants = createTourney();
    uint64_t participantCount = getParticipantCount(participants);
    uint64_t roundCount       = 0;

    if (participantCount % 2 == 0)
        roundCount = participantCount - 1;
    else
        roundCount = participantCount;

    clearScreen();
    printf("Participants Count: %3" PRIu64 "\t Rounds: %3" PRIu64 "\n",
           participantCount, roundCount);

    printParticipants(participants);
    return 0;
}
