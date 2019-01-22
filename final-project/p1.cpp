//
//  main.cpp
//  co_project
//
//  Created by 宋初文 on 12/9/18.
//  Copyright © 2018 宋初文. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
 * It reads in instructions from the input file
 * If it successefully reads in the instructions, then return true
 * Else return false
 */
bool getInstructions(const char argc[], vector<string> &instructions, map<string, int> & branches){
    ifstream myfile;
    myfile.open(argc);

    // If cannot open input file, then return false
    if (!myfile) return false;

    string instruction;
    int line_num = 0;
    while (getline(myfile, instruction)) {
        line_num++;
        instructions.push_back(instruction);
        // Check if this is a branch label by checking the last char
        int len = instruction.length();
        if (instruction[len - 1] == ':') {
            // Get the branch name
            string branch_name = instruction.substr(0, len - 1);
            // The branch starts from the next line
            branches[branch_name] = line_num;
        }
    }
    myfile.close();
    return true;
}


void set_cycleStages(vector<vector<string> > &cycle_stages, int i, int j, int current_stage){


    if (current_stage == 1) {
        for (int k = 0; k < j; k++) {
            cycle_stages[j].push_back(".");
        }
        cycle_stages[j].push_back("IF");
        for (int k = j + 1; k < 16; k++) {
            cycle_stages[j].push_back(".");
        }
    }
        // If there is * in current stage, then no need to change anything
    else if (cycle_stages[j][i] == "*") {
        return;
    }
    else if (current_stage == 2) {
        cycle_stages[j][i] = "ID";
    }
    else if (current_stage == 3) {
        // If the previous stage is *
        if (cycle_stages[j][i - 1] == "*") {
            cycle_stages[j][i] = "*";
        }
            // Otherwise
        else {
            cycle_stages[j][i] = "EX";
        }
    }
    else if (current_stage == 4) {
        // If the previous stage is *
        if (cycle_stages[j][i - 1] == "*") {
            cycle_stages[j][i] = "*";
        }
            // Otherwise
        else {
            cycle_stages[j][i] = "MEM";
        }
    }
    else if (current_stage == 5) {
        // If the previous stage is *
        if (cycle_stages[j][i - 1] == "*") {
            cycle_stages[j][i] = "*";
        }
            // Otherwise
        else {
            cycle_stages[j][i] = "WB";
        }
    }

    return;
}




std::string getOperation(string instruction, string &operation){
    // Get the length of this instruction
    int len = instruction.length();

    // If this is a branch label, then no operation and return "branch"
    if (instruction[len - 1] == ':') {
        return "branch";
    }
    // If this is nop, then return nop
    if (instruction == "nop") {
        return "nop";
    }

    int index = 0;
    // Get the length of operation
    while (instruction[index] != ' ') index++;

    operation = instruction.substr(0, index);

    if (operation == "bne" || operation == "beq") {
        return "J";
    }
    else {
        return "I";
    }
}


void read_instruction(const string instruction, string &destination, string &operand1, string &operand2, char type) {
    // If not J type
    if (type == 'N') {
        int operand_count = 0;
        for (int i = 0; i < (int)instruction.length(); i++) {
            if (instruction[i] == '$') {
                // If operand_count is 0, then it is the destination
                if (operand_count == 0) {
                    operand_count++;
                    destination = instruction.substr(i + 1, 2);
                }
                    // Else is operand2
                else if (operand_count == 1) {
                    // if this is $zero
                    if (instruction[i + 1] == 'z') {
                        operand1 = instruction.substr(i + 1, 4);
                    }
                    else {
                        operand1 = instruction.substr(i + 1, 2);
                    }
                    operand_count++;
                }
            }
            else if (instruction[i] == ',' && operand_count == 2) {
                // If the second operand is a register
                if (instruction[i + 1] == '$') {
                    operand2 = instruction.substr(i + 2, 2);
                }
                    // Else if the second operans is a number
                else {
                    operand2 = instruction.substr(i + 1, instruction.length() - i - 1);
                }
            }
        }
    }
        // If J type
    else if (type == 'J') {
        int operand_count = 0;
        for (int i = 0; i < (int)instruction.length(); i++) {
            if (instruction[i] == '$') {
                if (operand_count == 0) {
                    operand_count++;
                    operand1 = instruction.substr(i + 1, 2);
                }
                else if (operand_count == 1) {
                    operand2 = instruction.substr(i + 1, 2);
                }
            }
            // If operand_count is 1, that means we passed operand2 already
            if (operand_count == 1 && instruction[i - 1] == ',') {
                // Get the length of the name of the branch
                int len = instruction.length() - i;
                destination = instruction.substr(i, len);
            }
        }
    }
}

map<string, pair<int, int> > initialize_register_file() {
    map<string, pair<int, int> > ret;
    ret["s0"] = make_pair(0, 0);
    ret["s1"] = make_pair(0, 0);
    ret["s2"] = make_pair(0, 0);
    ret["s3"] = make_pair(0, 0);
    ret["s4"] = make_pair(0, 0);
    ret["s5"] = make_pair(0, 0);
    ret["s6"] = make_pair(0, 0);
    ret["s7"] = make_pair(0, 0);
    ret["t0"] = make_pair(0, 0);
    ret["t1"] = make_pair(0, 0);
    ret["t2"] = make_pair(0, 0);
    ret["t3"] = make_pair(0, 0);
    ret["t4"] = make_pair(0, 0);
    ret["t5"] = make_pair(0, 0);
    ret["t6"] = make_pair(0, 0);
    ret["t7"] = make_pair(0, 0);
    ret["t8"] = make_pair(0, 0);
    ret["t9"] = make_pair(0, 0);
    return ret;
}

void set_destinationStage(string destination, int current_stage, map<string, int> &destinations) {
    destinations[destination] = current_stage;
    return;
}

void update_registerFile(std::string operation, std::string destination, std::string operand1, std::string operand2,
                         std::map<std::string,std::pair<int, int> > & register_file){
    int v0, v1, v2;
    v0 = 0;
    if(operand1 == "zero"){
        v1 = 0;
    }
    else{
        v1 = register_file[operand1].second;
    }
    if(operation == "add" || operation == "and" || operation == "or" || operation == "slt"){
        v2 = register_file[operand2].second;
        if(operation == "add"){
            v0 = v1 + v2;
        }
        else if(operation == "and"){
            v0 = v1 & v2;
        }
        else if(operation == "or"){
            v0 = v1 ^ v2;
        }
        else if(operation == "slt"){
            if(v1 < v2){
                v0 = 1;
            }
            else{
                v0 = 0;
            }
        }
    }
    else{
        v2 = stoi(operand2);
        if(operation == "addi"){
            v0 = v1 + v2;
        }
        else if(operation == "andi"){
            v0 = v1 & v2;
        }
        else if(operation == "ori"){
            v0 = v1 ^ v2;
        }
        else if(operation == "slti"){
            if(v1 < v2){
                v0 = 1;
            }
            else{
                v0 = 0;
            }
        }
    }
    register_file[destination].second = v0;
}

void put_b_in_a(std::string destination, std::map<std::string,std::pair<int, int> > &register_file){
    register_file[destination].first = register_file[destination].second;
}


void get_value(std::string operand, std::map<std::string,std::pair<int, int> > register_file, int &operand_value){
    operand_value = register_file[operand].second;
}

void get_branchIndex(std::string const &destination, std::map<std::string, int> branches, int &next_instruction_index){
    next_instruction_index = branches[destination];
}

void print_cycle(std::vector<std::string> const &cycle_instructions, std::vector<std::vector<std::string> > const &cycle_stages,
                 std::map<std::string,std::pair<int, int> > register_file)
{
    std::cout << "CPU Cycles ===>     1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16" << std::endl;
    auto count = cycle_instructions.size();

    for(int i = 0; i < (int)count; i++){
        std::cout << left <<  setw(20) <<cycle_instructions[i];
        for(int j = 0; j < 16; j++){
            if(j != 15){
                std::cout << left << setw(4) <<cycle_stages[i][j];
            }
            else{
                std::cout << cycle_stages[i][j] << "\n";
            }
        }
    }
    std::cout << "\n";

    cout << "$s0 = " << left << setw(14) <<register_file["s0"].first;
    cout << "$s1 = " << left << setw(14) <<register_file["s1"].first;
    cout << "$s2 = " << left << setw(14) <<register_file["s2"].first;
    cout << "$s3 = " << register_file["s3"].first << "\n";
    cout << "$s4 = " << left << setw(14) <<register_file["s4"].first;
    cout << "$s5 = " << left << setw(14) <<register_file["s5"].first;
    cout << "$s6 = " << left << setw(14) <<register_file["s6"].first;
    cout << "$s7 = " << register_file["s7"].first << "\n";
    cout << "$t0 = " << left << setw(14) <<register_file["t0"].first;
    cout << "$t1 = " << left << setw(14) <<register_file["t1"].first;
    cout << "$t2 = " << left << setw(14) <<register_file["t2"].first;
    cout << "$t3 = " << register_file["t3"].first << "\n";
    cout << "$t4 = " << left << setw(14) <<register_file["t4"].first;
    cout << "$t5 = " << left << setw(14) <<register_file["t5"].first;
    cout << "$t6 = " << left << setw(14) <<register_file["t6"].first;
    cout << "$t7 = " << register_file["t7"].first << "\n";
    cout << "$t8 = " << left << setw(14) <<register_file["t8"].first;
    cout << "$t9 = " << register_file["t9"].first << endl;
    cout <<"----------------------------------------------------------------------------------\n";
}


void add_stars(vector<vector<string> > &cycle_stages, int instruction_index, int cycle){
    cycle_stages[instruction_index][cycle] = "*";
}

int get_nopNumber(std::string operand1, std::string operand2, map<string, int> destinations){
    int tmp;
    map<string, int>::iterator it1, it2;
    it1 = destinations.find(operand1);
    it2 = destinations.find(operand2);
    if(it1 != destinations.end() && it2 != destinations.end()){
        tmp = min(destinations[operand1], destinations[operand2]);
        if(tmp > 6){
            return 0;
        }
        else {
            return 6 - tmp;
        }
    }
    else if(it1 != destinations.end()){
        tmp = destinations[operand1];
        if(tmp > 6){
            return 0;
        }
        else {
            return 6 - tmp;
        }
    }
    else if(it2 != destinations.end()){
        tmp = destinations[operand2];
        if(tmp > 6){
            return 0;
        }
        else {
            return 6 - tmp;
        }
    }
    else{
        return 0;
    }
}

void insert_nop(int nop_num, vector<vector<string> > &cycle_stages, vector<string> &cycle_instructions, int j, int i) {
    // Insert nop into cycle_instructions[j]
    cycle_instructions.insert(cycle_instructions.begin() + j, nop_num, "nop");

    vector<string> temp_stage = cycle_stages[j];
    temp_stage[i] = "*";
    cycle_stages.insert(cycle_stages.begin() + j, nop_num, temp_stage);
    cycle_stages[j + nop_num][i] = "ID";
    if (cycle_stages[j + nop_num+1].size()!=0){
        cycle_stages[j + nop_num+1][i] = "IF";
    }
    return;
}

void set_cycleStages_no_forwarding(vector<vector<string> > &cycle_stages, int i, int j, int current_stage, vector<int> &nop_num) {
    if (nop_num[j] > 0) {
        cycle_stages[j][i] = cycle_stages[j][i - 1];
        nop_num[j]--;
        return;
    }
    else if (current_stage == 1) {
        for (int k = 0; k < j; k++) {
            cycle_stages[j].push_back(".");
        }
        cycle_stages[j].push_back("IF");
        for (int k = j + 1; k < 16; k++) {
            cycle_stages[j].push_back(".");
        }
    }
    else if ((cycle_stages[j][i - 1] == "*" && cycle_stages[j][i - 3] == "IF") || (cycle_stages[j][i - 1] == "*" && cycle_stages[j][i - 3] == "ID")) {
        cycle_stages[j][i] = "*";
        return;
    }
    
    else if (current_stage == 2) {
        cycle_stages[j][i] = "ID";
    }
    else if (current_stage == 3) {
        cycle_stages[j][i] = "EX";
    }
    else if (current_stage == 4) {
        cycle_stages[j][i] = "MEM";
    }
    else if (current_stage == 5 && cycle_stages[j][i-1] != "*") {
        cycle_stages[j][i] = "WB";
    }
    return;
}


int main(int argc, const char * argv[]) {
    if (argc != 3){
        return 1;
    }

    std::vector<std::string> instructions;
    std::map<std::string, int> branches;
    std::map<std::string, int> destinations;
    std::map<std::string,std::pair<int, int> > register_file = initialize_register_file();


    std::vector<std::string> cycle_instructions;
    std::vector<std::vector<std::string> > cycle_stages;
    vector<string> temp;
    for (int i = 0; i < 16; i++) {
        cycle_stages.push_back(temp);
    }
    //read instructions into vector
    getInstructions(argv[2], instructions, branches);
    if (!strncmp(argv[1], "F", 1)){
        cout << "START OF SIMULATION (forwarding)" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
        int next_instruction_index = 0;
        for (int i = 0; i < 16; i++){
            for (int j = 0; j <= (int)cycle_instructions.size(); j++){
                std::string current_instruction;
                std::string operation;
                std::string instruction_type;
                if (j==i){//only update the last instruction of this cycle, the previous instructions remain the same
                    //check if cycle_instructions[j] is empty, if not, that means in the j type instruction we've already pushback the next instruction
                    if ((int)cycle_instructions.size()!=j+1){
                        if (next_instruction_index>= (int)instructions.size()){
                            break;
                        }
                        instruction_type = getOperation(instructions[next_instruction_index],operation);
                        if (instruction_type == "branch"){//skip lable
                            next_instruction_index++;
                        }
                        cycle_instructions.push_back(instructions[next_instruction_index]);
                        next_instruction_index++;
                    }
                }
                if (j==(int)cycle_instructions.size()){//last instruction
                    break;
                }
                current_instruction = cycle_instructions[j];
                //get current_stage
                int current_stage;
                current_stage = i-j+1;
                set_cycleStages(cycle_stages, i, j, current_stage);


                //get operation

                instruction_type = getOperation(current_instruction,operation);
                std::string destination;
                std::string operand1;
                std::string operand2;

                if (instruction_type != "J"){
                    //get destination, operands
                    read_instruction(current_instruction, destination, operand1, operand2, 'N');
                    if(current_stage == 3){
                        update_registerFile(operation, destination, operand1, operand2, register_file);
                    }

                }
                if (instruction_type=="J"){
                    read_instruction(current_instruction, destination, operand1, operand2, 'J');
                    if(current_stage==5){

                        int operand1_value;
                        int operand2_value;
                        get_value(operand1, register_file, operand1_value);
                        get_value(operand2, register_file, operand2_value);
                        //compare operands, decide whether to take the branch
                        if ((operation=="beq" && operand1_value==operand2_value) ||(operation=="bne" && operand1_value!=operand2_value)){

                            //update next three cycle_stages as *
                            for(int k = 1; k<4;k++){
                                add_stars(cycle_stages, j+k, i);
                            }
                            //add_star(cycle_stages, instruction_index, stage);
                            //get the branch number, pushback the first line content of the branch to the cycle_instructions
                            get_branchIndex(destination, branches, next_instruction_index);
                            cycle_instructions.push_back(instructions[next_instruction_index]);
                            next_instruction_index++;
                        }

                    }
                }

                if(current_stage==5 && find(cycle_stages[j].begin(), cycle_stages[j].end(),"*")==cycle_stages[j].end()){
                    put_b_in_a(destination, register_file);
                }
                if (j == (int)cycle_instructions.size()-1 && current_stage==5){
                    //print cycle_instructions, cycle_stages, register_file
                    print_cycle(cycle_instructions, cycle_stages, register_file);
                    cout << "END OF SIMULATION" << endl;
                    return 0;
                }

            }
            //print cycle_instructions, cycle_stages, register_file
            print_cycle(cycle_instructions, cycle_stages, register_file);

        }
    }
    if (!strncmp(argv[1], "N", 1)){
        cout << "START OF SIMULATION (no forwarding)" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
        int next_instruction_index = 0;
        vector<int> nops_number;
        for (int i = 0; i < 16; i++){
            nops_number.push_back(0);
        }

        for (int i = 0; i < 16; i++){
            for (int j = 0; j <= (int)cycle_instructions.size(); j++){
                std::string current_instruction;
                std::string operation;
                std::string instruction_type;
                if (j==i){//only update the last instruction of this cycle, the previous instructions remain the same
                    //check if cycle_instructions[j] is empty, if not, that means in the j type instruction we've already pushback the next instruction
                    if ((int)cycle_instructions.size()!=j+1){
                        if (next_instruction_index>= (int)instructions.size()){
                            break;
                        }
                        instruction_type = getOperation(instructions[next_instruction_index],operation);
                        if (instruction_type == "branch"){//skip lable
                            next_instruction_index++;
                        }
                        cycle_instructions.push_back(instructions[next_instruction_index]);
                        next_instruction_index++;
                    }
                }
                if (j==(int)cycle_instructions.size()){//last instruction
                    break;
                }

                current_instruction = cycle_instructions[j];
                int current_stage;
                current_stage = i-j+1;
                

                //get operation

                instruction_type = getOperation(current_instruction,operation);
                std::string destination;
                std::string operand1;
                std::string operand2;
                if(instruction_type == "nop"){

                    set_cycleStages_no_forwarding(cycle_stages, i, j, current_stage, nops_number);
                }
                else if (instruction_type != "J"){
                    //get destination, operands
                    read_instruction(current_instruction, destination, operand1, operand2, 'N');
                    //update destination stage
                    set_destinationStage(destination, current_stage, destinations);
                    if(current_stage == 3){
                        //check operands are completed, if not add nop
                        int nop = get_nopNumber(operand1, operand2, destinations);
                        //int nop_number = get_nopNumber(operand1,operand2, destinations):6-smallest stage
                        if (nop){
                            if (nop==2){
                                //insert 2 nops before cycle_instructions j
                                //insert 2 cycle_stages[j] ending with * before cycle_stages[j]
                                insert_nop(nop, cycle_stages, cycle_instructions, j, i);
                                j = j+2;
                                //update nops_number
                                nops_number[j] = 1;
                                nops_number[j+1] = 1;
                                break;

                            }
                            if (nop == 1){
                                insert_nop(nop, cycle_stages, cycle_instructions, j, i);
                                j = j+1;
                                break;
                            }

                        }
                        set_cycleStages_no_forwarding(cycle_stages, i, j, current_stage, nops_number);

                    }
                    else if(current_stage == 5){
                        update_registerFile(operation, destination, operand1, operand2, register_file);
                        put_b_in_a(destination, register_file);
                        set_cycleStages_no_forwarding(cycle_stages, i, j, current_stage, nops_number);
                    }
                    else{
                        set_cycleStages_no_forwarding(cycle_stages, i, j, current_stage, nops_number);
                    }

                }
                else if (instruction_type=="J"){
                    read_instruction(current_instruction, destination, operand1, operand2, 'J');
                    set_destinationStage(destination, current_stage, destinations);
                    if(current_stage == 3){
                        //check operands are completed, if not add nop
                        int nop = get_nopNumber(operand1, operand2, destinations);
                        //int nop_number = get_nopNumber(operand1,operand2, destinations):6-smallest stage
                        if (nop){
                            if (nop==2){
                                //insert 2 nops before cycle_instructions j
                                //insert 2 cycle_stages[j] ending with * before cycle_stages[j]
                                insert_nop(nop, cycle_stages, cycle_instructions, j, i);
                                j = j+2;
                                //update nops_number
                                nops_number[j] = 1;
                                nops_number[j+1] = 1;


                            }
                            if (nop == 1){
                                insert_nop(nop, cycle_stages, cycle_instructions, j, i);
                                j = j+1;
                            }

                        }
                        else{
                            set_cycleStages_no_forwarding(cycle_stages, i, j, current_stage, nops_number);
                        }
                    }
                    else if(current_stage==5){
                        set_cycleStages_no_forwarding(cycle_stages, i, j, current_stage, nops_number);
                        int operand1_value;
                        int operand2_value;
                        get_value(operand1, register_file, operand1_value);
                        get_value(operand2, register_file, operand2_value);
                        //compare operands, decide whether to take the branch
                        if ((operation=="beq" && operand1_value==operand2_value) ||(operation=="bne" && operand1_value!=operand2_value)){

                            //update next three cycle_stages as *
                            //get the branch number, pushback the first line content of the branch to the cycle_instructions
                            get_branchIndex(destination, branches, next_instruction_index);
                            cycle_instructions.push_back(instructions[next_instruction_index]);
                            next_instruction_index++;
                            set_cycleStages(cycle_stages, i, j+4, 1);
                        }

                    }
                    else if(i!=j){
                        set_cycleStages_no_forwarding(cycle_stages, i, j, current_stage, nops_number);
                    }
                }


                if (j == (int)cycle_instructions.size()-1 && current_stage==5){
                    //print cycle_instructions, cycle_stages, register_file
                    print_cycle(cycle_instructions, cycle_stages, register_file);
                    cout << "END OF SIMULATION" << endl;
                    return 0;
                }

            }
            //print cycle_instructions, cycle_stages, register_file
            print_cycle(cycle_instructions, cycle_stages, register_file);
        }
    }
    cout << "END OF SIMULATION" << endl;
    return 0;
}
