/*
	Program Description:

	This program implements a simple social network system with support for individuals, businesses, groups, and organizations. It uses various structures and functions to create, manage, and interact with nodes representing entities in the social network.

	Structures:
	1. Node:
	   - Represents a generic node in the social network with essential information such as ID, links to other nodes, name, date, content, and type (individual, business, group, or organization).

	2. Individual:
	   - Inherits from Node and adds specific information for individuals, such as birthday.

	3. Location:
	   - Represents a geographical location with x and y coordinates.

	4. Business:
	   - Inherits from Node and adds information about a business, including its location, owners, and customers.

	5. Group:
	   - Inherits from Node and represents a group of nodes/members.

	6. Organisation:
	   - Inherits from Node and represents an organization with a location and members.

	7. SearchResult:
	   - A structure to store search results, including an array of nodes and the result size.

	8. Birthday:
	   - A structure to store birthdays in the format dd, mm, yyyy.

	ASSUMPTIONS MADE:
	- The maximum nodes in the network can be 100. This value can be changed by modifying the MAX_NODES macro.
	- I have used an array to store references of contents posted by nodes, so as to prevent duplication while allowing reposting. The maximum length and number of strings have been set as 100, this can be modified using the MAX_CONTENT macro.
	- Since the id has been made self incrementing (using global variable id in social.c), most of the functions performing RUD operations ask for the name of the node.

*/

#define MAX_NODES 100	// Set as a default value, can be changed as per requirement
#define MAX_CONTENT 100 // Set as a default value, can be changed as per requirement

typedef struct Node
{
	int id;
	struct Node **links;
	int num_links;
	char *name;
	char *date; // using the time.h header file to set the date in the format of a string
	char **content;
	int num_contents;
	char type; // I- individual, B- business, G- group, O- organisation
} Node;

extern Node *all_nodes[MAX_NODES];
extern int num_nodes;

extern char all_content[MAX_CONTENT][MAX_CONTENT];
extern int num_content;

typedef struct Birthday
{
	int day;
	int month;
	int year;
} Birthday;

typedef struct Individual
{
	Node node;
	Birthday birthday;
} Individual;

typedef struct Location
{
	double x;
	double y;
} Location;

typedef struct Business
{
	Node node;
	Location location;
	Individual **owners;
	int num_owners;
	Individual **customers;
	int num_customers;
} Business;

typedef struct Group
{
	Node node;
	Node **members;
	int num_members;
} Group;

typedef struct Organisation
{
	Node node;
	Location location;
	Individual *members;
	int num_members;
} Organisation;

typedef struct SearchResult
{
	Node **nodes;
	int size;
} SearchResult;

// Creates a new node.
Node *create_node(char *name, char type);
// Creates a new individual node.
Individual *create_individual(char *name, Birthday birthday);
// Creates a new business node.
Business *create_business(char *name, Location location);
// Creates a new group node.
Group *create_group(char *name);
// Creates a new organisation node.
Organisation *create_organisation(char *name, Location location);

// Function to add a member to a group or organisation. Groups can have businesses as members too.
void add_member(Node *group_or_org, Node *new_member);
// Function to add an owner or customer to a business.
void add_owner_or_customer(Business *business, Individual *new_owner_or_customer, char role);

// Deletes a node.
void delete_node(char *name);
// Utility function to remove links and finish deleting the node.
void remove_node_from_links(Node *node, Node *target);
// Search functions for searching by name, type or birthday (birthday, only for individuals)
SearchResult search_node_by_name(char *name);
SearchResult search_node_by_type(char type);
SearchResult search_individual_by_birthday(Birthday birthday);

// Utility function to check if a node is already linked to a node, so that duplicate links aren't created.
int is_node_in_links(Node *node, Node *target);
// Prints 1- hop linked nodes.
void print_linked_nodes(char *name);
// Function to post content in a node.
void post_content(char *name, char *content);
// Function to search by content and print the node which posted that content, allows partial content search too.
void search_and_print_content(char *name);
// Displays the contents of individuals linked to an individual.
void display_linked_content(char *name);

// Prints the details of a node, taking care of special fields for all types.
void print_node_details(Node *node);
// Prints all nodes in the network.
void print_all_nodes();
// The text-based interface.
void interface();