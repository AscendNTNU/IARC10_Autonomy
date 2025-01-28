#include"dumb_lawnmower.h"

/*////////////////////////////////////////////////////////////////////////////////////////////////
Author: Adrian
Programmet lager en liste med punkter i en rettlinje til motsatt side, for så å gå en rett linje tilbake.

starting_position er start posisjonen
end_vector er en vektor fra start punktet til ønsket slutt sted. BURDE IKKE ENDRE HØYDEN. 
path_vector er en vektor fra start til et punkt på motsatt side av området. 
resolution er antall punkter per sidelengde

*/////////////////////////////////////////////////////////////////////////////////////////////////


std::vector<NED> generate_path(NED starting_position, NED end_vector, NED path_vector, int resolution)
{
    assert(end_vector.down == 0 && path_vector.down == 0 && "Dette er feil sted å endre høyden, for da skjer det mellom to linjer.");

    std::vector<NED> output{starting_position};

    // På vei bort
    NED last = starting_position;
    for (int i = 1; i <= resolution; i++)
    {
        last += path_vector / (double)resolution;
        output.emplace_back(last);
    }

    // Flytte seg på motsatt side
    last += end_vector;
    output.emplace_back(last);


    // På vei tilbake
    for (int i = 1; i <= resolution; i++)
    {
        last -= path_vector / (double)resolution;
        output.emplace_back(last);
    }

    return output;
}


//////////////// Testing kode
// int main()
// {
//     NED 
//     start_position{0, 0, -6},
//     end_vector{4, 0, 0},
//     path_vector{0, 90, 0};

//     std::vector<NED> path = generate_path(start_position, end_vector, path_vector, 20);

//     for (auto &p : path)
//     {git
//         std::cout << p << "\n";
//     }

// }