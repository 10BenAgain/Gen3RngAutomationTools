## Description
Cross-platform CLI tool for searching encounters in Pokémon Fire Red and Leaf Green. My goal was to learn more about the C programming language and to avoid having to use the Gen3SeedAssistant tool through Wine on my Linux machine. 

## Installation
Minimal installation is required. Just extract the release files and run the program from your desired directory. There are two additional components that are required alongside the binary file, however. There is a `data` folder that must reside in the same directory as the binary and another `settings.ini` file that must be present as well. This will be briefly covered later. 

## Building
If you want to build this program from source, there are a couple of requirements.
1. Git
2. CMake (Yikes, I know)
3. A C Compiler (I just use gcc)
> This program requires a 3rd party C Library: [inih.c](https://github.com/benhoyt/inih.git) which is a simple .ini file parser and will need to be cloned using git. CMake should take care of this step automatically for you as long as you have git installed.

Start by cloning this repository by running `git clone https://github.com/10BenAgain/FRLG-Encounter-Search-Tool.git` then navigate to the newly cloned directory. Run the following:
```bash
mkdir build
cd build
cmake .. -USE_BUILD_PATH=ON
make
```
If everything went smoothly, you should now be left with an executable `bin`
## Usage
There are only 3 commands available in this program:

<pre><code>bin <span style="color: #19AC00">help</span>    <i><span style="color: #969696"># Prints all the commands, subcommands and available flags</span></i>
bin <span style="color: #FF7609">list</span>    <i><span style="color: #969696"># List relevant data components for search</span></i>
bin <span style="color: #e28743">search</span>  <i><span style="color: #969696"># Searches for targets</span></i>
</code></pre>

### <ins>List</ins> 
The list will be used to get the proper values for searching location indexes. For example, to find the appropriate index for `Route 1` in a list of `Grass` areas in Fire Red, run 
<pre><code>bin <span style="color: #FF7609">list</span> locations grass <span style="color: #FF5D42">fr</span></code></pre>
For Leaf Green, run
<pre><code>bin <span style="color: #FF7609">list</span> locations grass <span style="color: #599E00">lg</span></code></pre>

Below is a list of available location options to list:
```bash
'grass' # Any land areas (Route 1) 
'water' # Surfing 
'rock'  # Rock Smash
'old'   # Old Rod
'good'  # Good Rod
'super' # Super Rod
```
To see possible encounters for a specific location, you can run
<pre><code>bin <span style="color: #FF7609">list</span> encounter grass 46 lg</code></pre>

Where 46 corresponds to `Route 1` from the resulting list given from running the `locations grass lg` command.

Other subcommands for `list` include: 


| Name  | Description | Usage |
| ------------- | ------------- | - |
| natures   | Prints all nature strings and their stat boost information  | bin list natures|
|  gender   | Prints the 3 possible gender options used for searching  | bin list gender |
|   shiny   | Prints the 3 possible shiny types used for searching  | bin list shiny |
|  hidden   | Prints all Hidden Ability type strings  | bin list hidden |


### <ins>Search</ins>
Searching requires many arguments and configurations. To simplify the process, the program will search possible __known__ farmed seed values based on the `settings.ini` values only. By default, the program looks for a `settings.ini` file in its working directory that looks like this:
```ini
[player]
name=Ben            ; Currently unused, just for tracking profiles I guess
sid=34437           ; Secret ID
tid=44782           ; Trainer ID

[game]
version=LG          ; LG or FR
sub=10              ; 1.1 = 11 1.0 = 10
language=English    ; English, EU, Japanese

[settings]
audio=MONO          ; MONO or STEREO
seed=Start          ; Start, A, L
button=LA           ; LA, LR, or Help
```
The listed possible options for each field are listed in the comments. To change the values, you will have to manually edit them in your favorite text editor. In the example shown above, the program will ONLY use seeds from a baked in seed list with matching settings and version. 
> If you prefer to use a full set of custom seed lists, don't worry, there is a search flag available covered in the `flags` section later. 

The `settings.ini` file also eliminates the need to pass in trainer data to the programs' arguments. You can create multiple 'profiles' for the program to use. Before continuing, make sure to edit this file with the desired information and trainer data.

#### <ins>Static Search</ins>
Searching for static encounters requires the following arguments:
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #FEEB40">static</span> [Advances] [Pokemon] [Nature] [Level] [Ability] <span style="color: #2A8EC5">[HP] [ATK] [DEF] [SPA] [SPD] [SPE]</span> [Gender] [Shiny]
</code></pre>

> Ability argument takes an integer. Either 0 or 1 respectively. Since many Pokémon have the same ability for 0 and 1 (Bulbasaur only has Overgrow), if this is the case, the program will search for both.

Example:
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #FEEB40">static</span> 1000 Bulbasaur Docile 5 1 <span style="color: #2A8EC5">19 11 10 12 12 10</span> Male None
</code></pre>

#### <ins>Wild Search</ins>
Searching for wild encounters requires the following arguments:
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> [Advances] [Encounter Type] [Location] [Pokemon] [Nature] [Level] [Ability] <span style="color: #2A8EC5">[HP] [ATK] [DEF] [SPA] [SPD] [SPE]</span> [Gender] [Shiny]</code></pre>


Example:
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None</code></pre>

### <ins>Flags</ins>
Flags passed to the program must be added to the end of the search command to parsed correctly. (After the [Shiny] type is specified)

| Flag  | Description                                                                                                         | Args |
| ------------- |---------------------------------------------------------------------------------------------------------------------| - |
| 't'   | Adds an offset of 1 to seed list. (Holding Select)                                                                  | None  |
| 'h'   | Adds an offset of 12 to seed list (Holding A)                                                                       | None | | -h |
| 'm'   | Sets the wild search method. By default this is set to H1                                                           | H2 or H4 |
| 's'   | Sets the start point for advances. By default this is set to 0                                                      | Number |
| 'i'   | Tells the program to search on only one seed                                                                        | Number (Hex) |
| 'r'   | Specify the seed 'range' to search by instead of entire list. __"-i"__ MUST be set first and must proceed this flag | Number |
| 'y'   | For searching Unowns, specify the symbol to filter                                                                  | Character |
| 'P'   | Tells the program where to search for a settings.ini file                                                           | Path to File |
| 'L'   | Tells the program where to search for a custom seed list                                                            | Path to File |

#### <ins>Examples</ins>
Using the 't' or 'h' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -t</code></pre>
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -h</code></pre>
Using the 'm' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -m H4</code></pre>
Using the 's' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -s 800</code></pre>
> This will begin the search at advance 800 and stop 1000 so the resulting range will be 200 advances. By default, the program will search all advances up to 1000 if this flag is not set.

Using the 'i' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -i 0xE585</code></pre>
> Instead of using the entire seed list for the given settings.ini parameters, searches with an initial seed of the one provided (0xE585) and ignores all the rest

Using the 'r' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -i 0xE585 -r 50</code></pre>
> This flag REQUIRES the -i flag to be set BEFORE it. Essentially this will search your active seed list for the passed seed (0xE585) and make sure it exists. If yes, a new seed list will be generated with 50 seeds below the target and 50 seed above the target. This is meant to decrease the processing time by not searching every single possible known seed. 

Using the 'y' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> search wild 1000 grass 90 Unown Relaxed <span style="color: #2A8EC5">25 0 64 44 35 47 33 28</span> None None -y C </code></pre>
> Since Unown's are handled slightly differently, a flag is required to filter further into the Unown symbol if needed. In the example above, the program will search only for Unown-C

Using the 'P' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -P C:\Users\RNG\settings2.ini</code></pre>
> Settings must match the structure as described the beginning of the search section

Using the 'L' flag
<pre><code>bin <span style="color: #e28743">search</span> <span style="color: #7FBD81">wild</span> 1000 grass 37 Ditto Rash 30 1 <span style="color: #2A8EC5">75 41 37 42 30 41</span> None None -P C:\Users\RNG\MySeedList.txt</code></pre>
To use a custom list of seeds, you will need to create one. The structure is very simple and looks like this:

```
34748,A080
34764,ECC6
34780,36A8
34804,7F44
```
Where the first number is the intro timer and the second is the seed value. Since the seed timer is unused for this program, it can be just left as 0. Create your list as a text file. An example custom seed list is included in the download folder of this program named `MyCustomSeedList.txt`
> Sometimes if you have your custom seed list open in a text editor and the program tries to read it, it may read garbage data so make sure to save and close the file before running the search.

## Planned Improvements
- [ ] Add RSE Support 
- [ ] Add blanket searching flags
- [ ] Add Search all possible seeds (As opposed to all known)
- [ ] Migrate parts of this program to Web Assembly for browser use
- [ ] General optimizations
## Credits
This program would not be possible without the help from everyone in Blisy's retail RNG [Discord](https://discord.com/invite/YUpyEVh) server who have been extremely helpful in answering my questions. Special thank you to:
1. Blisy - [YouTube](https://www.youtube.com/@imablisy) - [GitHub](https://github.com/notblisy) 
2. [Lincoln](https://github.com/Lincoln-LM) for help with Jump and Encounter tables as well as RNG basics
3. Shao (shaonova on Discord) for pointing me to the right directions for the game decompilations
4. [Admiral Fish](https://github.com/Admiral-Fish) for creating PokeFinder which this program is primarily based on
5. [Mucks](https://github.com/MucksW) PID Reroll and other helpful information
6. All the cool RNG people that do RNG for these games