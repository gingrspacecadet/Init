# === Usage ===
There are 2 modes: 
**Basic** and **Advanced**

## === Basic ===
Basic mode is initiated using the command `init`. It will display a faux-ui in the terminal. To navigate, use the arrow keys. It is split into sections:

### === Project Name ===
This section determines project name and location.

### === Primary Language ===
Only allows one language.

### === Extras ===
These are extra addons to your project.

#### === Git ===
Initialises a git repository in your project, using the default branch name. More control can be achieved using advanced mode.

## === Advanced ===
Instead of a ui, this mode takes in all parameters using command-line arguments. An argument is specified by beginning with a '-', anything else will be targeted to the previous argument.

### === Arguments ===
`-n`/`--name`: the name of your project.
`-o`/`--location`: the location of your project. If excluded, defaults to current working directory.
`-l`/`--language`: the language to be used in your project.
`-e`/`--extras`: Any extras to add. Must be the final argument, as any subsequent ones are directed at the extras.
