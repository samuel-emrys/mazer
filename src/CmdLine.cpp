/**
 * @file CmdLine.cpp
 *
 * @brief Implementation of CmdLine class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/CmdLine.h"

bool CmdLine::parseArgs()
{
	const int MIN_ARGS = 2;
	const int NEXT_ELEMENT = 1;
	const int MAX_INT_ARGS = 3;
	const int FIRST_ARG = 1;
	const int PROG_NAME_INDEX = 0;

	const std::string flagSearch = "--";
	const std::string gaFlag = "--ga"; //generate using aldous broder
	const std::string geFlag = "--ge"; //generate using ellers
	const std::string pmFlag = "--pm"; //solve using dijkstra's manhattan
	const std::string peFlag = "--pe"; //solve using dijkstra's euclidean
	const std::string pbFlag = "--pb"; //solve using breadth first search
	const std::string pdFlag = "--pd"; //solve using depth first search
	const std::string lbFlag = "--lb"; //load binary
	const std::string svFlag = "--sv"; //save svg
	const std::string sbFlag = "--sb"; //save binary
	const std::string hFlag = "--h"; //help
	const std::string mazeExt = ".maze"; //binary extension
	const std::string svgExt = ".svg"; //svg extension

	//struct to hold the data for each flag and their arguments
	struct Argument temp;

	//ensures minimum arguments input
	if (argc < MIN_ARGS)
	{
		throw ArgumentException(argv[PROG_NAME_INDEX], 
			"Minimum number of arguments not satisfied. Use '--h' to see "
				"correct usage.");
	}
	//loops through command line args
	for (int i = 0; i < argc; i++)
	{
		//checks for "--" in string to determine if a flag
		unsigned long found = argv[i].find(flagSearch);
		if (found != std::string::npos)
		{
			temp.flag = argv[i];
			//generate flag
			if (temp.flag.compare(gaFlag) == 0 || 
				temp.flag.compare(geFlag) == 0)
			{
				//loops through all arguments following "--ga"
				for (int j = i+NEXT_ELEMENT; j < argc; j++)
				{
					try
					{
						//holds numeric arguments for "--ga"
						temp.intValues.push_back(stoul(argv[j]));
					}
					/*catches exception when stoul tries to convert a letter to
					a number */
					catch (std::invalid_argument& e)
					{
						unsigned long flag_check = argv[j].find(flagSearch);
						//check if there is a flag in the folowing argument
						//throws exception if there isn't
						if (flag_check == std::string::npos)
						{
							throw ArgumentException(gaFlag,
								"Argument must be numeric only. Use '--h' to "
									"see correct usage.");
						}
						//terminates loop if there is a flag
						break;
					}
				}
				//check if there are more than 3 numeric arguments for "--g"
				if (temp.intValues.size() > MAX_INT_ARGS)
				{
					throw ArgumentException(argv[i], 
						std::to_string(temp.intValues.size()) +
						 " Arguments provided. Maximum number of "
						 "arguments exceeded Use '--h' to see correct usage.");
				}
			}
//			else if (temp.flag.compare(geFlag) == 0)
//			{
//				//generate ellers method
//			}
			//load binary, save binary and save svg case
			else if (temp.flag.compare(lbFlag) == 0 || 
				temp.flag.compare(sbFlag) == 0 || 
				temp.flag.compare(svFlag) == 0)
			{
				std::string ext;
				unsigned long ext_check=0;

				//stores string arguments (filename)
				if (argc > i+NEXT_ELEMENT)
				{
					temp.stringValue = argv[i+NEXT_ELEMENT];
				}
				else
				{
					throw ArgumentException(argv[i], "Insufficient "
						"Arguments.");
				}

				//flag and extension check variables
				unsigned long flag_check = 
					argv[i+NEXT_ELEMENT].find(flagSearch);
				/*ensures appropriate file extension for comparison and
				exceptions are used */
				if (temp.flag.compare(lbFlag) == 0 || 
					temp.flag.compare(sbFlag) == 0)
				{
					ext_check = argv[i+NEXT_ELEMENT].find(mazeExt);
					ext = mazeExt;
				}
				else if (temp.flag.compare(svFlag) == 0)
				{
					ext_check = argv[i+NEXT_ELEMENT].find(svgExt);
					ext = svgExt;
				}
				/*check to see if next argument has a flag or is blank.
				 Indicates that there's no filename provided */
				if (flag_check != std::string::npos || 
					argv[i+NEXT_ELEMENT] == "")
				{
					throw ArgumentException(argv[i], "Insufficient arguments."
						" Use '--h' to see correct usage.");
				}
				//ensures the filename contains ".maze" or ".svg" as relevant
				else if (ext_check == std::string::npos)
				{
					throw FileException(argv[i+NEXT_ELEMENT], 
						"Invalid file type. File isn't a '"+ext+"' file. "
						"Use '--h' to see correct usage.");
				}
			}
			/*solve; dijkstras(manhattan), dijkstras(euclidean),
			breadth first search, depth first search*/
			else if ((temp.flag.compare(pmFlag) == 0) ||
					(temp.flag.compare(peFlag) == 0) || 
					(temp.flag.compare(pbFlag) == 0) || 
					(temp.flag.compare(pdFlag) == 0))
			{
                if (!solverSpecified)
                {
                	//ensures that only one solver is given as input args
                    solverSpecified = true;
                }
                else
                {
                    throw ArgumentException(argv[i], "Cannot specify more "
                     "than one method to solve the maze. "
                     "Use --h to see correct usage");
                }
			}
			//help flag
			else if (temp.flag.compare(hFlag) == 0)
			{
				/*ensures help flag is a valid input. Originally, there was 
					a field for the struct named "description", however it was
					unused and so removed*/
			}
			else
			{
				throw ArgumentException(argv[i], "Invalid Flag. Use '--h' "
					"to see correct usage.");
			}
			//adds the temp struct to the struct vector
			args.push_back(temp);		
		}
		//if the first argument is not a flag
		else if (found == std::string::npos && i == FIRST_ARG)
		{
			throw ArgumentException(argv[i], "Invalid Flag. Use '--h' to "
				"see correct usage.");
		}
	}
    int svgFlagIndex = -1;
    int solveFlagIndex = -1;
    
    for (unsigned i = 0; i < args.size(); i++)
    {
        if (args[i].flag.compare(svFlag) == 0)
        {
            svgFlagIndex = i;
        }
        else if (args[i].flag.compare(pdFlag) == 0 ||
		         args[i].flag.compare(pbFlag) == 0 ||
		         args[i].flag.compare(pmFlag) == 0 ||
		         args[i].flag.compare(peFlag) == 0)
        {
            solveFlagIndex = i;
        }
    }
    if ((solveFlagIndex != -1 && svgFlagIndex != -1) 
    	&& (solveFlagIndex > svgFlagIndex))
    {
        Argument holder = args[svgFlagIndex];
        args[svgFlagIndex] = args[solveFlagIndex];
        args[solveFlagIndex] = holder;
    }
    
	return true;
}

void CmdLine::displayUsage() //displays usage when user enters "--h" as an arg
{
	std::cout << "How to use this program:" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "You may enter several input arguments to mazer, and alter "
		" it's operation accordingly." << std::endl;
	std::cout << "These flags are as follows: " << std::endl;

	std::cout <<"\t --ga : Generate a Maze using Aldous Broder algorithm.\n"
	"\t --ge : Generate a Maze using Ellers algorithm.\n"
	"\t These require no input arguments "
		"for random generation, and also accepts the following arguments:" 
		<< std::endl;
	std::cout <<"\t\t seed : Specify a seed generator" << std::endl;
	std::cout <<"\t\t width : Specify a maze width" << std::endl;
	std::cout <<"\t\t height : Specify a maze height" << std::endl;
	std::cout << "" << std::endl;
	std::cout <<"\t\t EXAMPLE USAGE: " << std::endl;
	std::cout <<"\t\t --ga" << std::endl;
	std::cout <<"\t\t --ga seed" << std::endl;
	std::cout <<"\t\t --ga width height" << std::endl;
	std::cout <<"\t\t --ga seed width height" << std::endl;

	std::cout << "" << std::endl;
	std::cout <<"\t --lb : Load a maze from binary file. The following "
		"arguments must be specified:" << std::endl;
	std::cout <<"\t\t filename.maze : Name of the binary file" << std::endl;
	std::cout << "" << std::endl;
	std::cout <<"\t\t EXAMPLE USAGE: " << std::endl;
	std::cout <<"\t\t --lb filename.maze" << std::endl;

	std::cout << "" << std::endl;
	std::cout <<"\t --sb : Save a maze to binary file. The following arguments"
		" must be specified:" << std::endl;
	std::cout <<"\t\t filename.maze : Name of the binary file" << std::endl;
	std::cout << "" << std::endl;
	std::cout <<"\t\t EXAMPLE USAGE: " << std::endl;
	std::cout <<"\t\t --sb filename.maze" << std::endl;

	std::cout << "" << std::endl;
	std::cout <<"\t --sv : Save a maze to SVG file. The following arguments "
		"must be specified:" << std::endl;
	std::cout <<"\t\t filename.svg : Name of the SVG file" << std::endl;
	std::cout << "" << std::endl;
	std::cout <<"\t\t EXAMPLE USAGE: " << std::endl;
	std::cout <<"\t\t --sv filename.svg" << std::endl;

	std::cout << "" << std::endl;
	std::cout <<"\t --pb : Solve maze using breadth first search" << std::endl;
	std::cout <<"\t --pd : Solve maze using depth first search" << std::endl;
	std::cout <<"\t --pe : Solve maze using Dijkstras algorithm, using "
		"euclidean distance heuristics" << std::endl;
	std::cout <<"\t --pm : Solve maze using Dijkstras algorithm, using "
		"manhattan distance heuristics" << std::endl;

	std::cout << "" << std::endl;
	std::cout <<"PLEASE NOTE:" << std::endl;
	std::cout <<"The flags --g and --lb cannot be used together." << std::endl;
	std::cout <<"The input arguments must contain ONE of either --g OR --lb. "
		"It cannot contain both." << std::endl;
	std::cout <<"Both --g and --lb and their arguments are required to preceed"
		" --sb and --sv" << std::endl;
	std::cout <<"In order to save a maze to both binary and SVG, use both --sb"
		" and --sv input arguments" << std::endl;
	std::cout << "" << std::endl;
	std::cout <<"EXAMPLE USAGE: " << std::endl;
	std::cout <<"\t ./mazer --lb filename.maze" << std::endl;
	std::cout <<"\t ./mazer --lb filename.maze --sv filename.svg --pd" 
		<< std::endl;
	std::cout <<"\t ./mazer --g" << std::endl;
	std::cout <<"\t ./mazer --g --sb filename.maze --sv filename.svg --pe" 
		<< std::endl;
	std::cout <<"\t ./mazer --g seed --sv filename.svg" << std::endl;
	std::cout <<"\t ./mazer --g width height filename.maze --pa" << std::endl;
	std::cout <<"\t ./mazer --g seed width height --sb filename.maze" 
		<< std::endl;
}

