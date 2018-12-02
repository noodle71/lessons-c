/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION: 
 *
 * Our beloved boss, Mark Zuckemborg, wants a new feature for his amazing
 * social network FAILBOOK. He wants to find new friends for their users.
 *
 * Each profile, should be registered using this structure:
 *
 * typedef struct{
 *   int id;
 *   char name[100];
 *   int friends[100];
 *   int num_friends;
 * }T_PROFILE;
 * 
 * Within each T_PROFILE, we have the internal ID of the user, the name of the
 * user and the array of friends. The array of friends, contains the IDs
 * of all the user's friends.
 *
 * To do this:
 * We have to read a binary file named "friend.dat" which stores all
 * the information of the people registered within the platform.
 * 
 * First we read the number of registered people within the file using
 * the function:
 * int NumberUsers(FILE *f_profiles);
 *
 * Then, we allocate memory to read the file again and store each profile
 * in the array of T_PROFILE. We use the function:
 * void LoadProfilesFromFile(FILE *f_profiles, int num_profiles, T_PROFILE *v_profiles);
 *
 * Once we have read all the profiles, we have to show a menu:
 * 1- Show all users.
 * 2- Show possible friends for a user.
 * 3. Exit.
 * 
 * 1- User select first option: Program displays all users ID and Name.
 * Use the function:
 * void ShowAllProfiles(T_PROFILE *v_profiles, int num_profiles);
 *
 * 2- When the operator selects the second option, he has to select
 * the ID of one user. We need to validate that the user ID is in the
 * array. Using this function:
 * int IndexOfUser(T_PROFILE *v_profiles, int num_profiles, int id);
 *
 * This function returns the index of the array for the first user found 
 * which ID is the same. If the user is not found, we have to return -1.
 *
 * Once we have the user, we have to show the ID and name of users who
 * can be possible friends. To find possible friends, we follow these rules:
 * - We CAN'T show people who is already friend of the user.
 *   Code the function:
 *   int IndexOfFriend(T_PROFILE user, int id_friend);
 *   This function receives one user and the id of the friend. If it's found
 *   within the user.friends array, we should return the index, otherwise
 *   we should return -1.
 *
 * - The user can't be friend of himself.
 *
 * - We have to iterate over all the profiles. If a profile has one or more
 *   friends in common with the selected user, then we must show a message
 *   like this:
 *   ID: 3 	NAME: Jose (4 friends in common).
 *   ID: 5 	NAME: Esther (3 friends in common).
 *   ID: 6 	NAME: Luis (1 friends in common).
 *   We must use this function to discover friends in common:
 *   int FindCommonFriends(T_PROFILE user, T_PROFILE possible_friend);
 *   This function, returns the number of friends in common.
 *   Use also the previous function IndexOfFriend.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#define N 100

typedef struct{
  int id;
  char name[N];
  int friends[N];
  int num_friends;
}T_PROFILE;

int NumberUsers(FILE *f_profiles);
void LoadProfilesFromFile(FILE *f_profiles, int num_profiles, T_PROFILE *v_profiles);
void ShowAllProfiles(T_PROFILE *v_profiles, int num_profiles);
int IndexOfUser(T_PROFILE *v_profiles, int num_profiles, int id);
int IndexOfFriend(T_PROFILE user, int id_friend);
int FindCommonFriends(T_PROFILE user, T_PROFILE possible_friend);

int main(void){
  int num_profiles;
  FILE *f_profiles;
  T_PROFILE *v_profiles;
  int option;
  int found;
  int i;
  int common;
  int id;

  f_profiles = fopen("friend.dat","rb");
  if(f_profiles != NULL){
    num_profiles = NumberUsers(f_profiles);
    if(num_profiles > 0){
      v_profiles = (T_PROFILE *) calloc(num_profiles, sizeof(T_PROFILE));
      if(v_profiles != NULL){
	LoadProfilesFromFile(f_profiles, num_profiles, v_profiles);
	do{
	  printf("\n\nMENU:");
	  printf("\n1 - Show all users.");
	  printf("\n2 - Show possible friends for a user.");
	  printf("\n3 - Exit.");
	  printf("\nEnter option: ");
	  scanf("%d", &option);
	  switch(option){
	    case :
	    default:
	      printf("\nERROR: Invalid option.");
	  }
	}while(option != 3);
	free(v_profiles);
      }
    }
    fclose(f_profiles);
  }
  return 0;
}

/*
 * Get the number of profiles using the file.
 * INPUT: File.
 * OUTPUT: Number of users.
 */ 
int NumberUsers(FILE *f_profiles){
  int counter = 0;
  T_PROFILE p;

  while(fread(&p, sizeof(T_PROFILE), 1, f_profiles) == 1){
    counter++;
  }
  return counter;
}

/*
 * Load all users profiles from file.
 * INPUT: The file, the number of users and the array where the info will be stored.
 * OUTPUT: None.
 */ 
void LoadProfilesFromFile(FILE *f_profiles, int num_profiles, T_PROFILE *v_profiles){
  int i;
  rewind(f_profiles);
  for(i = 0; i < num_profiles; i++){
    fread(&v_profiles[i], sizeof(T_PROFILE), 1, f_profiles);
  }
  return;
}

/*
 * Display all profiles.
 * INPUT: Array of profiles and number of profiles.
 * OUTPUT: None.
 */ 
void ShowAllProfiles(T_PROFILE *v_profiles, int num_profiles){
  int i;
  int j;
  for(i = 0; i < num_profiles; i++){
    printf("\nID: %d\tNAME: %s", v_profiles[i].id, v_profiles[i].name);
    printf("\nFriends ID: ");
    for(j = 0; j < v_profiles[i].num_friends; j++){
      if(j == v_profiles[i].num_friends -1){
	printf("%d", v_profiles[i].friends[j]);
      }else{
        printf("%d, ", v_profiles[i].friends[j]);
      }
    }
  }
  return;
}

/*
 * Function returns the index of the first profile found which ID is
 * the same.
 * INPUT: The array of profiles, the number of profiles and the ID to look for.
 * OUTPUT: -1 if is not found, otherwise, returns the index of the array.
 */ 
int IndexOfUser(T_PROFILE *v_profiles, int num_profiles, int id){
  int i;
  int found = -1;
  for(i = 0; i < num_profiles && found == -1; i++){
    if(v_profiles[i].id == id){
      found = i;
    }
  }
  return found;
}

/*
 * Returns the first index of the array of user.friends which ID is the same.
 * INPUT: User profile and the ID of the user.
 * OUTPUT: -1 if is not found, otherwise, returns the index of the array.
 */ 
int IndexOfFriend(T_PROFILE user, int id_friend){
  int i;
  int found = -1;
  for(i = 0; i < user.num_friends && found == -1; i++){
    if(user.friends[i] == id_friend){
      found = i;
    }
  }
  return found;
}

/*
 * Find friends in common.
 * INPUT: The user profile and the possible_friend profile.
 * OUTPUT: The number of friends in common.
 */ 
int FindCommonFriends(T_PROFILE user, T_PROFILE possible_friend){
  int count = 0;
  int found;
  int i;
  //The possible friend and the user are not the same person.
  if(user.id != possible_friend.id){ 
    //The user is not our friend.
    found = IndexOfFriend(user, possible_friend.id);
    if(found < 0){     
      for(i = 0; i < possible_friend.num_friends; i++){
	found = IndexOfFriend(user, possible_friend.friends[i]);
        if(found >= 0){
	  count++;
	}
      }
    }
  }
  return count;
}
