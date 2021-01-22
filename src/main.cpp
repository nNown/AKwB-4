#include <iostream>
#include <instance.h>
#include <instance_parser.h>
#include <instance_generator.h>
#include <cstdlib>
#include <time.h>
#include <tuple>
#include <map>

bool findRestrictionMap(Instance& instance, const int& depth);

// Należy zaimplementować algorytm dokładny (przeszukiwanie z nawrotami, o złożoności wykładniczej) realizujący następujące czynności:
// − wczytanie z pliku instancji problemu mapowania metodą częściowego trawienia (multizbioru A);
// − skonstruowanie mapy restrykcyjnej zgodnej z podanym multizbiorem (wystarczy jedna z możliwych map);
// − wypisanie rezultatu na wyjściu w sposób czytelny dla użytkownika; w razie braku rozwiązania (gdyby instancja zawierała błędy) użytkownik powinien zostać poinformowany odpowiednim komunikatem.

// W sprawozdaniu należy zamieścić: opis algorytmu, zawartość wygenerowanych instancji, wyniki przeprowadzonych testów: uzyskana mapa i czas obliczeń (czas poniżej 10 sek. należy podać z dokładnością do setnych sekundy), wnioski.

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    
    InstanceParser* instanceParser = InstanceParser::Parser();
    InstanceGenerator* instanceGenerator = InstanceGenerator::Generator();

    auto instance = Instance(instanceParser->LoadInstance(argv[1]));
    if(instance.ExpectedMapFragments() > 0) {
        std::cout << "Restriction map: "; 
        bool found = findRestrictionMap(instance, 0);
        if(!found) std::cout << "not found" << std::endl;
    } else {
        std::cout << "Instance doesn't contain any possible result" << std::endl;
    }

    return 0;
}

bool findRestrictionMap(Instance& instance, const int& depth) {
    int mapLength = 0;
    for(auto& fragment : instance.Map()) {
        mapLength += fragment;
    }

    if(depth == instance.ExpectedMapFragments()) {
        if(mapLength == instance.SequenceLength()) {
            for(auto& fragment : instance.Map()) {
                std::cout << fragment << " ";
            }
            std::cout << std::endl;
            return true;
        }
        return false;
    }

    if(depth == 0) {
        int secondLongestFragment = 0;
        for(auto& [ fragment, usedCount ] : instance.RestrictiveDigestion()) {
            if(fragment > secondLongestFragment && fragment < instance.SequenceLength()) {
                secondLongestFragment = fragment;
            }
        }

        int firstFragment = instance.SequenceLength() - secondLongestFragment;
        if(instance.useFragment(firstFragment, false)) {
            instance.Map().push_back(firstFragment);
            findRestrictionMap(instance, depth + 1);
        }
    } else {
        for(auto& [ fragment, usedCount ] : instance.RestrictiveDigestion()) {
            if(instance.useFragment(fragment, false)) {
                instance.Map().push_back(fragment);

                if(!findRestrictionMap(instance, depth + 1)) {
                    instance.Map().pop_back();
                    instance.useFragment(fragment, true);
                }

            }

        }  
    }
    return false;
}