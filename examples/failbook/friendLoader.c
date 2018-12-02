/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION: 
 *
 * Our beloved boss, Mark Zuckemborg, wants a new feature for his amazing
 * social network FAILBOOK. He wants to create a file with a collection 
 * of all the profiles registered within the platform.
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
 *
 * First, we ask the operator the amount of users we want to register 
 * within our social network. Using the function:
 * void LoadAllProfiles(T_PROFILE *p_profiles, int num_profiles);
 *
 * We will fill al the profiles BUT we won't fill the array of friends.
 *
 * To create each profile, we will use the function:
 * void LoadOneProfile(T_PROFILE *p_profile);
 *
 * Once the profiles are collected. We will ask the operator to enter
 * each friend for each user. 
 *
 * We will iterate over all the profiles showing the operator a menu 
 * with three options:
 * 1- See all users.
 * 2- Add friend.
 * 3- Continue to next user.
 *
 * 1.- If the operator selects the first option, then, the list of all registered
 * users should be displayed. The operator just want to see the ID of each user
 * and the name. We must code this function to do this:
 * void PrintAllProfiles(T_PROFILE *p_profiles, int num_profiles);
 *
 * 2.- If the operator selects the second option, the operator should enter the ID
 * of the user to add that profile as friend. We can use the 
 * function:
 * void AddFriendToUser(T_PROFILE *p_profiles, int num_profiles, int id_user, int id_friend);
 *
 * That function should check that:
 * The friend is not the user himself. The id_user is not equal to id_friend.
 * The friend exists as registered user using this function:
 *
 * int IndexOfProfile(T_PROFILE *p_profiles, int num_profiles, int id);
 * The arguments of the functions are: the array of profiles, the number
 * of profiles and the ID to look for within the array.
 *
 * This function, should return the index of the first profile found in the 
 * array which ID is equal to the ID we are passing as parameter. 
 * If the ID is not found, we have to return -1.
 * 
 * 3.- When the operator press the third option, we have to skip to the next
 * user and show the menu again to enter that user's friends. If we have 
 * added all users friends, then all profiles should be writen within a file 
 * named friends.dat
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100

typedef struct{
  int id;
  char name[N];
  int friends[N];
  int num_friends;
}T_PROFILE;

void LoadAllProfiles(T_PROFILE *p_profiles, int num_profiles);
void LoadOneProfile(T_PROFILE *p_profile);
int IndexOfProfile(T_PROFILE *p_profiles, int num_profiles, int id);
void AddFriendToUser(T_PROFILE *p_profiles, int num_profiles, int id_user, int id_friend);
void PrintAllProfiles(T_PROFILE *p_profiles, int num_profiles);

void CleanString(char str[]);

int main(void){
  int option;
  int num_profiles;
  T_PROFILE *p_profiles;
  FILE *f_profiles;
  int i;
  int id_user;
  int id_friend;

  do{
    printf("\nEnter the number of users within Failbook: ");
    scanf("%d", &num_profiles);
    if(num_profiles <= 0 && num_profiles > N){
      printf("\nERROR: Number of users must be greater than 0.");
    }
  }while(num_profiles <= 0 && num_profiles > N);

  p_profiles = (T_PROFILE *)calloc(num_profiles, sizeof(T_PROFILE));
  if(p_profiles != NULL){
    LoadAllProfiles(p_profiles, num_profiles);
    for(i = 0; i < num_profiles; i++){
      do{
        printf("\n\nUser ID: %d\t\tNAME: %s", p_profiles[i].id, p_profiles[i].name);
	printf("\n1 - See profiles list.");
	printf("\n2 - Add friend to profile.");
	printf("\n3 - Continue with next user.");
	printf("\nEnter option: ");
	scanf("%d", &option);
	switch(option){
	  case 1:
	    PrintAllProfiles(p_profiles, num_profiles);
	    break;
	  case 2:
	    id_user = p_profiles[i].id;
	    printf("\nEnter friend ID: ");
	    scanf("%d", &id_friend);
	    AddFriendToUser(p_profiles, num_profiles, id_user, id_friend);
	    break;
	  case 3:
	    if(i == num_profiles - 1){
	      printf("\nAll users info completed.\n");
	    }
	    break;
	  default:
	    printf("\nERROR: Invalid option.");
	}
      }while(option != 3);
    }
    f_profiles = fopen("friend.dat", "wb");
    if(f_profiles != NULL){
      fwrite(p_profiles, sizeof(T_PROFILE), num_profiles, f_profiles);
      fclose(f_profiles);
    }
    free(p_profiles);
  }else{
    printf("\nERROR: Unable to allocate memory.\n");
  }
  return 0;
}

/*
 * Load all profiles info (Except friends).
 * INPUT: Profiles array and the number of profiles.
 * OUTPUT: None.
 */ 
void LoadAllProfiles(T_PROFILE *p_profiles, int num_profiles){
  int i;
  int index;
  for(i = 0; i < num_profiles; i++){
    LoadOneProfile(&p_profiles[i]);
  }
  return;
}

/*
 * Load one profile info (Except friends).
 * INPUT: Profile.
 * OUTPUT: None.
 */ 
void LoadOneProfile(T_PROFILE *p_profile){
  printf("\nID: ");
  scanf("%d", &(p_profile->id));
  getchar();
  printf("\nName: ");
  fgets(p_profile->name, N, stdin);
  CleanString(p_profile->name);
  return;
}

/*
 * Looks for a profile ID within the array of profiles.
 * INPUT: The array of profiles, the number of profiles and the ID
 * to look for.
 * OUTPUT: If it's found, return the index of the profile within the array,
 * otherwise, return -1.
 */ 
int IndexOfProfile(T_PROFILE *p_profiles, int num_profiles, int id){
  int i;
  int found = -1;
  for(i = 0; i < num_profiles && found == -1; i++){
    if(p_profiles[i].id == id){
      found = i;
    }
  }
  return found;
}

/*
 * Add a friend to a profile.
 * INPUT: The array of profiles, the number of profiles, the ID of the user and the 
 * ID of the friend.
 * OUTPUT: Returns 0 when it's not OK, otherwise, returns 1.
 */ 
void AddFriendToUser(T_PROFILE *p_profiles, int num_profiles, int id_user, int id_friend){
  int user_index = IndexOfProfile(p_profiles, num_profiles, id_user);
  int friend_index = IndexOfProfile(p_profiles, num_profiles, id_friend);
  int number_friends;
  if(id_user != id_friend && friend_index >= 0 && user_index >= 0){
    number_friends = p_profiles[user_index].num_friends;
    if(number_friends < num_profiles - 1){
      p_profiles[user_index].friends[number_friends] = id_friend;
      p_profiles[user_index].num_friends += 1;
    }else{
      printf("\nERROR: Max number of friends limit exceeded.");
    }
  }
  else if(id_user == id_friend){
    printf("\nERROR: User can't be friend of himself.");
  }
  else if(friend_index < 0){
    printf("\nERROR: Friend not found.");
  }
  else{
    printf("\nERROR: User not found.");
  }
  return;
}

/*
 * Print all users ID and name.
 * INPUT: Array of profiles and the number of profiles.
 * OUTPUT: None.
 */ 
void PrintAllProfiles(T_PROFILE *p_profiles, int num_profiles){
  int i;
  int j;
  for(i = 0; i < num_profiles; i++){
    printf("\nID: %d\t\tNAME: %s", p_profiles[i].id, p_profiles[i].name);
  }
  return;
}

/*
 * Removes the \n from a string
 * INPUT: String
 * OUTPUT: None.
 */ 
void CleanString(char str[]){
  str[strcspn(str, "\n")] = 0;
}
