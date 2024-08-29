#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

void problem_008(void)
{
    col_limited_printf(80, 0, "Problem: 008 - Largest Product in a Series\n");
    col_limited_printf(
        80, 0,
        "Description: The four adjacent digits in the 1000-digit number that "
        "have the greatest product are 9 imes 9 imes 8 imes 9 = 5832.\n"
    );
    /*printf(*/
    /*"73167176531330624919225119674426574742355349194934\n969835203127745063"*/
    /*"26239578318016984801869478851843\n858615607891129494954595017379583319"*/
    /*"52853208805511\n12540698747158523863050715693290963295227443043557\n66"*/
    /*"896648950445244523161731856403098711121722383113\n62229893423380308135"*/
    /*"336276614282806444486645238749\n30358907296290491560440772390713810515"*/
    /*"859307960866\n70172427121883998797908792274921901699720888093776\n6572"*/
    /*"7333001053367881220235421809751254540594752243\n5258490771167055601360"*/
    /*"4839586446706324415722155397\n5369781797784617406495514929086256932197"*/
    /*"8468622482\n83972241375657056057490261407972968652414535100474\n821663"*/
    /*"70484403199890008895243450658541227588666881\n164271714799244429282308"*/
    /*"63465674813919123162824586\n178664583591245665294765456828489128831426"*/
    /*"07690042\n24219022671055626321111109370544217506941658960408\n07198403"*/
    /*"850962455444362981230987879927244284909188\n84580156166097919133875499"*/
    /*"200524063689912560717606\n05886116467109405077541002256983155200055935"*/
    /*"729725\n71636269561882670428252483600823257530420752963450\n"*/
    /*);*/
    col_limited_printf(
        80, 0,
        "7316717653133062491922511967442657474235534919493496983520312774506326"
        "2395783180169848018694788518438586156078911294949545950173795833195285"
        "3208805511125406987471585238630507156932909632952274430435576689664895"
        "0445244523161731856403098711121722383113622298934233803081353362766142"
        "8280644448664523874930358907296290491560440772390713810515859307960866"
        "7017242712188399879790879227492190169972088809377665727333001053367881"
        "2202354218097512545405947522435258490771167055601360483958644670632441"
        "5722155397536978179778461740649551492908625693219784686224828397224137"
        "5657056057490261407972968652414535100474821663704844031998900088952434"
        "5065854122758866688116427171479924442928230863465674813919123162824586"
        "1786645835912456652947654568284891288314260769004224219022671055626321"
        "1111093705442175069416589604080719840385096245544436298123098787992724"
        "4284909188845801561660979191338754992005240636899125607176060588611646"
        "7109405077541002256983155200055935729725716362695618826704282524836008"
        "23257530420752963450\n"
    );
    col_limited_printf(
        80, 0,
        "Goal: Find the thirteen adjacent digits in the 1000-digit number "
        "that have the greatest product. What is the value of this product?\n"
    );

    const char *big_evil =
        "7316717653133062491922511967442657474235534919493496983520312774506326"
        "2395783180169848018694788518438586156078911294949545950173795833195285"
        "3208805511125406987471585238630507156932909632952274430435576689664895"
        "0445244523161731856403098711121722383113622298934233803081353362766142"
        "8280644448664523874930358907296290491560440772390713810515859307960866"
        "7017242712188399879790879227492190169972088809377665727333001053367881"
        "2202354218097512545405947522435258490771167055601360483958644670632441"
        "5722155397536978179778461740649551492908625693219784686224828397224137"
        "5657056057490261407972968652414535100474821663704844031998900088952434"
        "5065854122758866688116427171479924442928230863465674813919123162824586"
        "1786645835912456652947654568284891288314260769004224219022671055626321"
        "1111093705442175069416589604080719840385096245544436298123098787992724"
        "4284909188845801561660979191338754992005240636899125607176060588611646"
        "7109405077541002256983155200055935729725716362695618826704282524836008"
        "23257530420752963450";

    uint64_t res         = 0;
    uint64_t window_size = 13;
    for (uint64_t i = 0; i < strlen(big_evil) - window_size; i++) {
        uint64_t partial_res = 1;
        for (uint64_t j = 0; j < window_size; j++) {
            partial_res *= (big_evil[i + j] - '0');
        }

        if (partial_res > res)
            res = partial_res;
    }

    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}