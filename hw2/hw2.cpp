#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef struct properties
{
	unsigned long long DisplayURL;
	unsigned long long AdvertiserID;
	unsigned long long KeywordID;
	unsigned long long TitleID;
	unsigned long long DescriptionID;
} Properties;
typedef struct query
{
	int click[4][4];
	int impression[4][4];
	bool clicked;
} Query;
typedef struct ad
{
	int totalclick;
	int totalimpression;
	bool impressed;
	map<int, Query> Query_map;
	vector<Properties> Properties_vector;
} Ad;	
typedef struct user { map<int, Ad> Ad_map; } User;

void Properties_print(const Properties& P)
{
	putchar('\t');
	printf("%llu %llu %llu %llu %llu\n", P.DisplayURL, P.AdvertiserID, P.KeywordID, P.TitleID, P.DescriptionID);
}

bool Properties_compare(const Properties& i, const Properties& j)
{
	if(i.DisplayURL < j.DisplayURL)
		return 1;
	if(i.DisplayURL > j.DisplayURL)
		return 0;
	if(i.AdvertiserID < j.AdvertiserID)
		return 1;
	if(i.AdvertiserID > j.AdvertiserID)
		return 0;
	if(i.KeywordID < j.KeywordID)
		return 1;
	if(i.KeywordID > j.KeywordID)
		return 0;
	if(i.TitleID < j.TitleID)
		return 1;
	if(i.TitleID > j.TitleID)
		return 0;
	if(i.DescriptionID < j.DescriptionID)
		return 1;
	if(i.DescriptionID > j.DescriptionID)
		return 0;
	return 0;
}

int Properties_equal(const Properties& i, const Properties& j)
{
	if(i.DisplayURL != j.DisplayURL)
		return 0;
	if(i.AdvertiserID != j.AdvertiserID)
		return 0;
	if(i.KeywordID != j.KeywordID)
		return 0;
	if(i.TitleID != j.TitleID)
		return 0;
	if(i.DescriptionID != j.DescriptionID)
		return 0;
	return 1;
}

void stars(void)
{
	int i;
	for(i = 1; i <= 20; i++)
		putchar('*');
	putchar('\n');
}

void get(int u, int a, int q, int p, int d, map<int, User>& User_map)
{
	stars();
    printf("%d ",User_map[u].Ad_map[a].Query_map[q].click[p][d]);
    printf("%d\n",User_map[u].Ad_map[a].Query_map[q].impression[p][d]);
	stars();
}

void clicked(map<int, Ad>& Ad_map)
{
	stars();
    map<int, Ad>::iterator i;
    map<int, Query>::iterator j;
    for(i = Ad_map.begin(); i != Ad_map.end(); ++i)
    {
	    for(j = (i->second).Query_map.begin(); j != (i->second).Query_map.end(); ++j)
        {
            if((j->second).clicked)
                printf("%d %d\n", i->first, j->first);
        }
    }
	stars();
}

void findproperties(const vector<Properties>& Properties_vector_1, const vector<Properties>& Properties_vector_2)
{
	int size= Properties_vector_1.size() + Properties_vector_2.size();
	vector<Properties> Properties_vector_all;
	Properties_vector_all.insert(Properties_vector_all.end(), Properties_vector_1.begin(), Properties_vector_1.end());
	Properties_vector_all.insert(Properties_vector_all.end(), Properties_vector_2.begin(), Properties_vector_2.end());
	sort(Properties_vector_all.begin(), Properties_vector_all.end(), Properties_compare);
	int i = 1;
	Properties_print(Properties_vector_all[0]);
	while(i < size)
	{
		if(!Properties_equal(Properties_vector_all[i - 1], Properties_vector_all[i]))
			Properties_print(Properties_vector_all[i]);
		i++;
	}
}

void impressed(map<int, Ad>& Ad_map1, map<int, Ad>& Ad_map2)
{
	stars();
    map<int, Ad>::iterator i;
    map<int, Ad>::iterator j;
	i = Ad_map1.begin();
	j = Ad_map2.begin();
	while((i != Ad_map1.end()) && (j != Ad_map2.end()))
	{
		if((i->first) < (j->first))
			i++;
		else if((i->first) > (j->first))
			j++;
		else if((i->second).impressed && (j->second).impressed)
		{
			printf("%d\n",(i->first));
			findproperties((i->second).Properties_vector, (j->second).Properties_vector);
			i++;
			j++;
		}
	}
	stars();
}

void profit(int a, double theta, map<int, User>& User_map)
{
	stars();
    map<int, User>::iterator i;
    map<int, Ad>::iterator j;
    double r;
    for(i = User_map.begin(); i != User_map.end(); ++i)
    {
        j = (i->second).Ad_map.find(a);
        if(j != (i->second).Ad_map.end())
        {
            r = (double)(j->second).totalclick/ (double)(j->second).totalimpression;
            if(r >= theta)
				printf("%d\n",(i->first));
        }
    }
	stars();
}

int main(int agrc, char* argv[])
{
	FILE *input;
	input = fopen(argv[1], "r");
	map<int, User> User_map;
	int Click = 0, Impression = 0, AdID = 0, Depth = 0, Position = 0, QueryID = 0, UserID = 0;
	unsigned long long DisplayURL = 0, AdvertiserID = 0, KeywordID = 0, TitleID = 0, DescriptionID = 0;
	
	int i, j;
	char c;
	while((c = fgetc(input)) != EOF)
	{
		Click = c - '0';
		while((c = fgetc(input)) != '\t')
		{
			Click *= 10;
			Click += c - '0';
		}
		
		Impression = 0;
		while((c = fgetc(input)) != '\t')
		{
			Impression *= 10;
			Impression += c - '0';
		}
		
		DisplayURL = 0;
		while((c = fgetc(input)) != '\t')
		{
			DisplayURL *= 10;
			DisplayURL += c - '0';
		}
		
		AdID = 0;
		while((c = fgetc(input)) != '\t')
		{
			AdID *= 10;
			AdID += c - '0';
		}
		
		AdvertiserID = 0;
		while((c = fgetc(input)) != '\t')
		{
			AdvertiserID *= 10;
			AdvertiserID += c - '0';
		}
		
		Depth = 0;
		while((c = fgetc(input)) != '\t')
		{
			Depth *= 10;
			Depth += c - '0';
		}
		
		Position = 0;
		while((c = fgetc(input)) != '\t')
		{
			Position *= 10;
			Position += c - '0';
		}
		
		QueryID = 0;
		while((c = fgetc(input)) != '\t')
		{
			QueryID *= 10;
			QueryID += c - '0';
		}
		
		KeywordID = 0;
		while((c = fgetc(input)) != '\t')
		{
			KeywordID *= 10;
			KeywordID += c - '0';
		}
		
		TitleID = 0;
		while((c = fgetc(input)) != '\t')
		{
			TitleID *= 10;
			TitleID += c - '0';
		}
		
		DescriptionID = 0;
		while((c = fgetc(input)) != '\t')
		{
			DescriptionID *= 10;
			DescriptionID += c - '0';
		}
		
		UserID = 0;
		while((c = fgetc(input)) != '\n' && !feof(input))
		{
			UserID *= 10;
			UserID += c - '0';
		}
		
		if(User_map.find(UserID) == User_map.end())
		{
			Query Q;
			for(i = 0; i <= 3; i++)
			{
				for(j = 0; j <= 3; j++)
				{
					Q.click[i][j] = 0;
					Q.impression[i][j] = 0;
				}
			}
			Q.clicked = false;
			if(Click > 0)
				Q.clicked = true;
			Q.click[Position][Depth] = Click;
			Q.impression[Position][Depth] = Impression;
			
			Ad A;
			A.impressed = false;
			if(Impression > 0)
			{
				A.impressed = true;				
				Properties P;
				P.DisplayURL = DisplayURL;
				P.AdvertiserID = AdvertiserID;
				P.KeywordID = KeywordID;
				P.TitleID = TitleID;
				P.DescriptionID = DescriptionID;
				A.Properties_vector.push_back(P);
			}
			A.totalclick = Click;
			A.totalimpression = Impression;
			A.Query_map.insert(pair<int, Query>(QueryID, Q));
			
			User U;
			U.Ad_map.insert(pair<int, Ad>(AdID, A));
			
			User_map.insert(pair<int, User>(UserID, U));
		}
		else if(User_map[UserID].Ad_map.find(AdID) == User_map[UserID].Ad_map.end())
		{
			Query Q;
			for(i = 0; i <= 3; i++)
			{
				for(j = 0; j <= 3; j++)
				{
					Q.click[i][j] = 0;
					Q.impression[i][j] = 0;
				}
			}
			Q.clicked = false;
			if(Click > 0)
				Q.clicked = true;
			Q.click[Position][Depth] = Click;
			Q.impression[Position][Depth] = Impression;
			
			Ad A;
			A.impressed = false;
			if(Impression > 0)
			{
				A.impressed = true;				
				Properties P;
				P.DisplayURL = DisplayURL;
				P.AdvertiserID = AdvertiserID;
				P.KeywordID = KeywordID;
				P.TitleID = TitleID;
				P.DescriptionID = DescriptionID;
				A.Properties_vector.push_back(P);
			}
			A.totalclick = Click;
			A.totalimpression = Impression;
			A.Query_map.insert(pair<int, Query>(QueryID, Q));
			
			User_map[UserID].Ad_map.insert(pair<int, Ad>(AdID, A));
		}
		else if(User_map[UserID].Ad_map[AdID].Query_map.find(QueryID) == User_map[UserID].Ad_map[AdID].Query_map.end())
		{
			Query Q;
			for(i = 0; i <= 3; i++)
			{
				for(j = 0; j <= 3; j++)
				{
					Q.click[i][j] = 0;
					Q.impression[i][j] = 0;
				}
			}
			Q.clicked = false;
			if(Click > 0)
				Q.clicked = true;
			Q.click[Position][Depth] = Click;
			Q.impression[Position][Depth] = Impression;
			
			if(Impression > 0)
			{
				User_map[UserID].Ad_map[AdID].impressed = true;
				Properties P;
				P.DisplayURL = DisplayURL;
				P.AdvertiserID = AdvertiserID;
				P.KeywordID = KeywordID;
				P.TitleID = TitleID;
				P.DescriptionID = DescriptionID;
				User_map[UserID].Ad_map[AdID].Properties_vector.push_back(P);
			}
			User_map[UserID].Ad_map[AdID].totalclick += Click;
			User_map[UserID].Ad_map[AdID].totalimpression += Impression;
			
			User_map[UserID].Ad_map[AdID].Query_map.insert(pair<int, Query>(QueryID, Q));
		}
		else
		{
			User_map[UserID].Ad_map[AdID].Query_map[QueryID].click[Position][Depth] += Click;
			User_map[UserID].Ad_map[AdID].Query_map[QueryID].impression[Position][Depth] += Impression;
			
			if(Click > 0)
				User_map[UserID].Ad_map[AdID].Query_map[QueryID].clicked = true;
			
			if(Impression > 0)
			{
				User_map[UserID].Ad_map[AdID].impressed = true;
				Properties P;
				P.DisplayURL = DisplayURL;
				P.AdvertiserID = AdvertiserID;
				P.KeywordID = KeywordID;
				P.TitleID = TitleID;
				P.DescriptionID = DescriptionID;
				User_map[UserID].Ad_map[AdID].Properties_vector.push_back(P);
			}
			
			User_map[UserID].Ad_map[AdID].totalclick += Click;
			User_map[UserID].Ad_map[AdID].totalimpression += Impression;
		}
	}
	fclose(input);
	
	char command[10];
	int u, a, q, p, d, u1, u2;
	double theta;
	while(scanf("%s", command) != EOF)
	{
		if(strcmp(command, "get") == 0)
		{
			scanf("%d%d%d%d%d", &u, &a, &q, &p, &d);
			get(u, a, q, p, d, User_map);
		}
		else if(strcmp(command, "clicked") == 0)
		{
			scanf("%d", &u);
			clicked(User_map[u].Ad_map);
		}
		else if(strcmp(command, "impressed") == 0)
		{
			scanf("%d%d", &u1, &u2);
			impressed(User_map[u1].Ad_map, User_map[u2].Ad_map);
		}
		else if(strcmp(command, "profit") == 0)
		{
			scanf("%d%lf", &a, &theta);
			profit(a, theta, User_map);
		}	
		else if(strcmp(command, "quit") == 0)
			return 0;
		else
			puts("Illegal Command");
	}	
}




