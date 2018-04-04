/*
 * const* vs *const
 */

// const *char: pointer can change, value cannot
char name[4] = {'d','a','v','e'};
char blah[4] = {'b','l','a','h'};
const *char dave = name;
//	DAVE[2] = 's';	// ERROR
name = blah;        // LEGAL

// char *const: value can change, pointer cannot
char name[4] = {'d','a','v','e'};
char blah[4] = {'b','l','a','h'};
char *const dave = name;
name[2] = 's';      // LEGAL
//	DAVE = BLAH;	// ERROR
