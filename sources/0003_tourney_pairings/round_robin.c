#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "tourney_std.h"

int main(void)
{
    clearScreen();
    Participant *participants = createTourney();
    uint64_t participantCount = getParticipantCount(participants);
    uint64_t roundCount =
        (participantCount % 2 == 0) ? participantCount - 1 : participantCount;

    clearScreen();
    printf(
        "\nParticipants Count: %3" PRIu64 "\t Rounds: %3" PRIu64 "\n",
        participantCount, roundCount
    );

    printParticipants(participants);
    return 0;
}
