//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include "Synonym.h"
#include <fstream>

/**
 * Appends the specified Literal to the end of literals list.
 *
 * @param literal element to be appended to the list
 */
void Synonym::addLiteral(const Literal& literal) {
    literals.emplace_back(literal);
}

/**
 * Returns the element at the specified position in literals list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in the list
 */
Literal Synonym::getLiteral(int index) const{
    return literals.at(index);
}

/**
 * Returns the element with the specified name in literals list.
 *
 * @param name name of the element to return
 * @return the element with the specified name in the list
 */
Literal Synonym::getLiteral(const string& name) const{
    for (Literal literal:literals){
        if (literal.getName() == name){
            return literal;
        }
    }
}

/**
 * Returns size of literals list.
 *
 * @return the size of the list
 */
int Synonym::literalSize() const{
    return literals.size();
}

/**
 * Returns <tt>true</tt> if literals list contains the specified literal.
 *
 * @param literal element whose presence in the list is to be tested
 * @return <tt>true</tt> if the list contains the specified element
 */
bool Synonym::contains(const Literal& literal) const{
    for (const Literal &current : literals){
        if (current == literal){
            return true;
        }
    }
    return false;
}

/**
 * Returns <tt>true</tt> if literals list contains the specified String literal.
 *
 * @param literalName element whose presence in the list is to be tested
 * @return<tt>true</tt> if the list contains the specified element
 */
bool Synonym::containsLiteral(const string& literalName) const{
    for (const Literal& current : literals){
        if (current.getName() == literalName){
            return true;
        }
    }
    return false;
}

/**
 * Removes the first occurrence of the specified element from literals list,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param toBeRemoved element to be removed from the list, if present
 */
void Synonym::removeLiteral(const Literal& toBeRemoved) {
    for (auto it = literals.begin() ; it != literals.end(); ++it){
        if (*it == toBeRemoved){
            literals.erase(it);
            break;
        }
    }
}

/**
 * Method to write Synonyms to the specified file in the XML format.
 *
 * @param outfile BufferedWriter to write XML files
 */
void Synonym::saveAsXml(ofstream& outfile) {
    outfile << "<SYNONYM>";
    for (Literal literal:literals){
        literal.saveAsXml(outfile);
    }
    outfile << "</SYNONYM>";
}

/**
 * Overridden toString method to print literals.
 *
 * @return concatenated literals
 */
string Synonym::to_string() const{
    string result;
    for (const Literal& literal : literals){
        result += literal.getName() + " ";
    }
    return result;
}

vector<Synonym> Synonym::getUniqueLiterals() {
    vector<Synonym> literalGroups;
    int groupNo = -1;
    Synonym synonym = Synonym();
    for (const Literal& literal : literals){
        if (literal.getGroupNo() != groupNo){
            if (groupNo != -1){
                literalGroups.emplace_back(synonym);
            }
            groupNo = literal.getGroupNo();
            synonym = Synonym();
        } else {
            if (groupNo == 0){
                literalGroups.emplace_back(synonym);
                synonym = Synonym();
            }
        }
        synonym.addLiteral(literal);
    }
    literalGroups.emplace_back(synonym);
    return literalGroups;
}
