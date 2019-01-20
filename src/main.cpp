/**
 * @file main.cpp
 *
 * @brief main function; initial program execution location
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/main.h"

int main(int argc, char ** argv)
{
	CmdLine cmd(argc, argv);
	Maze MazeObj;
    std::string solverString;
    std::string genString;
    std::string distance;
    float genTime;
    float svgTime;
    float binTime;
    float solveTime;
    
	//default seed value is time-variant
	unsigned long seed = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
	try
	{
		/*analyses and groups flags and their arguments for processing. Also
		* determines argument validity, but not the validity of the values*/
		cmd.parseArgs();
	}
	catch (const ArgumentException& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (const FileException& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: unforeseen exception. " << e.what() << '\n';
	}

	try
	{
		//loops through the flags
		for (unsigned i = 0; i < cmd.args.size(); i ++)
		{
			//Generate case
			if (cmd.args[i].flag.compare(gaFlag) == 0 ||
				cmd.args[i].flag.compare(geFlag) == 0)
			{
				//ensures maze hasn't already been generated
				if (!cmd.mazeGenerated)
				{
					/*if there are one or three arguments, gen seed value gets
					 * updated with user specified value*/
					if (cmd.args[i].intValues.size() == 1 ||
						 cmd.args[i].intValues.size() == 3)
					{
						seed = cmd.args[i].intValues[0];
					}
					//determines type of builder to use
                    enum builders builder_type;
                    if (cmd.args[i].flag.compare(gaFlag) == 0)
                    {
                        builder_type = ALDOUS;
                        genString = "Aldous";
                    }
                    else
                    {
                        builder_type = ELLERS;
                        genString = "Ellers";
                    }
                    //instantiates relevent builder
                    GetBuilder get_builder(MazeObj, seed);

                    auto gen = get_builder(builder_type);
                    Timer time;

					try
					{
						//switches number of arguments for "--g" flag
						switch (cmd.args[i].intValues.size())
						{
							case 0:
								gen->generate();
							break;

							case 1:
								gen->generate();
							break;

							case 2:	
								gen->generate((int)cmd.args[i].intValues[0],
									 (int)cmd.args[i].intValues[1]);
							break;

							case 3:
								gen->generate((int)cmd.args[i].intValues[1],
									 (int)cmd.args[i].intValues[2]);
							break;

							default:
								throw ArgumentException(gaFlag,
								std::to_string(cmd.args[i].intValues.size())
								 + " Arguments provided. Maximum number" 
								 	"of arguments exceeded. Use '--h' to see "
								 	"correct usage.");
							break;
						}
						//indicates maze has been generated
                        genTime = time.getDuration();
                        std::cout << "Time to generate: "
                        << genTime << " ms" << std::endl;
						cmd.mazeGenerated = true;
					}
					catch (const ArgumentException& e)
					{
						std::cerr << e.what() << '\n';
					}
				}
				else
				{
					throw MazeException("Maze has already been loaded.");
				}				
			}
			//load binary flag
			else if (cmd.args[i].flag.compare(lbFlag) == 0)
			{	
				//ensures maze hasn't been generated previously	
				if (!cmd.mazeGenerated)
				{
					try
					{
						//passes file name to maze object and load function
						MazeObj.loadBinary(cmd.args[i].stringValue);
						cmd.mazeGenerated = true;
					}
					catch (const FileException& e)
					{
						std::cerr << "Error: " << e.what() << '\n';
					}
				}
				else
				{
					throw MazeException("Maze has already been generated.");
				}
			}		
			//save svg flag
			else if (cmd.args[i].flag.compare(svFlag) == 0)
			{
				if (cmd.mazeGenerated)
				{
                    Timer saveTime;
					//passes file name to save svg function
					MazeObj.saveSVG(cmd.args[i].stringValue);
                    svgTime = saveTime.getDuration();
                    std::cout << "Time to save SVG: "
                    << svgTime << " ms" << std::endl;
				}
				else
				{
					throw MazeException("Maze hasn't been generated or loaded."
						" Use '--g' or '--lb' first.");
				}
			}
			//save binary flag
			else if (cmd.args[i].flag.compare(sbFlag) == 0)
			{
				if (cmd.mazeGenerated)
				{
                    Timer saveTime;
					//passes file name to save binary function
					MazeObj.saveBinary(cmd.args[i].stringValue);
                    binTime = saveTime.getDuration();
                    
                    std::cout << "Time to save binary: "
                    << binTime << " ms" << std::endl;
				}
				else
				{
					throw MazeException("Maze hasn't been generated or loaded."
						" Use '--g' or '--lb' first.");
				}
			}
            else if (cmd.args[i].flag.compare(pmFlag) == 0 ||
             		 cmd.args[i].flag.compare(peFlag) == 0 ||
             		 cmd.args[i].flag.compare(pdFlag) == 0 || 
             		 cmd.args[i].flag.compare(pbFlag) == 0)
            { //solver case

            	//determines solver type to be used
                enum solvers solver_type;
                enum distanceType distance_type;
                if (cmd.args[i].flag.compare(pdFlag) == 0)
                {
                    solver_type = DEPTH;
                    distance_type = NA;
                    solverString = "DFS";
                    distance = "";
                }
                else if (cmd.args[i].flag.compare(pbFlag) == 0)
                {
                    solver_type = BREADTH;
                    distance_type = NA;
                    solverString = "BFS";
                    distance = "NA";
                }
                else if(cmd.args[i].flag.compare(pmFlag) == 0)
                {
                    solver_type = DIJKSTRA;
                    distance_type = MANHATTAN;
                    solverString = "Dijkstra";
                    distance = "Manhattan";
                }
                else
                {
                    solver_type = DIJKSTRA;
                    distance_type = EUCLIDEAN;
                    solverString = "Dijkstra";
                    distance = "Euclidean";
                }
                //starting point and goal for maze solution
                int goal_X = MazeObj.getWidth()-1;
                int goal_Y = MazeObj.getHeight()-1;
                int startingPoint_X = 0;
                int startingPoint_Y = 0;
                
                //instantiates solver object
                GetSolver get_solver(MazeObj, goal_X, goal_Y, startingPoint_X,
                	startingPoint_Y);
                auto solver = get_solver(solver_type,distance_type);
                Timer solverTime;

                if(!solver->solveMaze())
                {
                	//determines solvability of maze
                    std::cerr << "ERROR: Unable to solve maze" << std::endl;
                }
                else
                {
                    solveTime = solverTime.getDuration();
                    std::cout << "Time solve using " << solverString
                    << "(" << distance << "): " << solveTime
                    << " ms" << std::endl;
                	//populates solution to maze object for printing
                    MazeObj.updateSolution(solver->getSolution());
                }
            }
			//help flag
			else if (cmd.args[i].flag.compare(hFlag) == 0)
			{
				cmd.displayUsage();
			}
		}

	}
	catch (const MazeException& e)
	{
		std::cerr << e.what() << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: unforeseen exception. " << e.what() << '\n';
	}
    
//    saveToFile(MazeObj.getWidth(), solverString, genString, distance);
	return EXIT_SUCCESS;
}