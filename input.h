struct input_dqueue * history;
char * buffer;
int buffer_size;
int history_size;
int buffer_index;
int default_buffer_size;
char key;
int keycode;

//inits the variables above sets buffer_size to b_size and history_size to h_size
//also sets inits the ncurses stuff for listen() to work
void input_init(int b_size, int h_size);

//adds to the buffer, location depends on buffer_index, afterwards it increases buffer_index by 1
//if buffer is too small then it expands it
void buffer_add(char new_char);

//creates a new buffer
void new_buffer(int b_size);

//default window is stdscr
//listens for input and sets key (for char) and keycode (for arrow keys and stuff)
//returns 0 if its a printable character and a 1 if its not a printable character
int listen();

//like listen but lets you choose which ncurses window to listen to
int wlisten(WINDOW *);