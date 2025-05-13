#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
#define N 853385
#define M1 4
#define M2 5
int read(){
	int w=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')f=c=='-'?-f:f,c=getchar();
	while(c>='0'&&c<='9')w=w*10+c-48,c=getchar();
	return w*f;
}
void col(int c1,int c2){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c1*16+c2);
}
char ch[100000];
string reads(){
	scanf("%[^\n]",ch);
	int n=strlen(ch);
	string res="";
	for(int i=0;i<n;i++)
		res.push_back(ch[i]);
	while(getchar()!='\n');
	return res;
}
string its(int x){
    if(!x)return 0;
	int t[10],cnt=0;
	while(x)t[++cnt]=x%10,x/=10;
	string s="";
	for(int i=cnt;i>0;i--)
		s=s+(char)('0'+t[i]);
    return s;
}
int sti(string s){
	int res=0,now=0,sz=s.size();
	while(s[now]<'0'||s[now]>'9')now++;
	while(now<sz&&s[now]>='0'&&s[now]<='9')res=res*10+s[now]-48,now++;
	return res;
}
bool isnum(string s){
	for(auto i:s)
		if(i<'0'||i>'9')return 0;
	return 1;
}
string Filelv(int x){
	int t[10],cnt=0;
	while(x)t[++cnt]=x%10,x/=10;
	string s="level/lv";
	for(int i=cnt;i>0;i--)
		s=s+(char)('0'+t[i]);
	s=s+".txt";
	return s;
}
string Filelevel(int x){
	int t[10],cnt=0;
	while(x)t[++cnt]=x%10,x/=10;
	string s="level/level";
	for(int i=cnt;i>0;i--)
		s=s+(char)('0'+t[i]);
	s=s+".txt";
	return s;
}
mt19937 rnd(time(NULL)^(unsigned long long)(new char));
int rad(int x,int y){
	return rnd()%(y-x+1)+x;
}
bool split(char x){
	if(x=='#')return 1;
	if(x=='\"')return 1;
	return 0;
}
bool vis[N],visch[65536];
int lv,hd;
int getc(const string&s,int x){
	return (1<<8)*(unsigned char)s[x]+(unsigned char)s[x+1];
}
int fv[1<<16];
struct poet{
	string ti,dy,au,co;
	void read(){
		scanf("%[^\n]",ch);
		int n=strlen(ch),now=1;
		while(ch[now]!='\"')ti.push_back(ch[now++]);
		now+=3;
		while(ch[now]!='\"')dy.push_back(ch[now++]);
		now+=3;
		while(ch[now]!='\"')au.push_back(ch[now++]);
		now+=2;
		while(now<n)co.push_back(ch[now++]);
		while(getchar()!='\n');
	}
	void init(){
		int sz=co.size();
		for(int i=0;i<sz-1;)
			if(split(co[i]))i++;
			else fv[getc(co,i)]++,i+=2;
	}
    int size(){
        return co.size();
    }
	bool check(){
		if(co.find("u")!=co.npos)return 0;
		if(co.find("?")!=co.npos)return 0;
		if(co.find("[")!=co.npos)return 0;
		if(co.find("]")!=co.npos)return 0;
		if(co.find("{")!=co.npos)return 0;
		if(co.find("}")!=co.npos)return 0;
		if(co.find("■")!=co.npos)return 0;
		return 1;
	}
	string get(int x=-1){
		int len=co.size(),id=x==-1?rad(0,len-1):x;
		while(split(co[id]))id=rad(0,len-1);
		int l=id,r=id;
		while(!split(co[l]))l--;
		while(!split(co[r]))r++;
		string res="";
		for(int i=l+1;i<r;i++)
			res.push_back(co[i]);
		return res;
	}
	void print(){
		printf("%s,%s,%s,%s\n",ti.c_str(),dy.c_str(),au.c_str(),co.c_str());
		// cout<<ti<<','<<dy<<','<<au<<','<<co<<endl;
	}
}p[N];
bool findout(string x){
	for(int i=0;i<N;i++)
		if(p[i].co.find(x)!=p[i].co.npos)return 1;
	return 0;
}
int getval(const string&s){
    int res=0,sz=s.size();
    for(int i=0;i<sz-1;)
        if(split(s[i]))i++;
        else{
            if(!visch[getc(s,i)])res+=fv[getc(s,i)],visch[getc(s,i)]=1;
            i+=2;
        }
    for(int i=0;i<sz-1;)
        if(split(s[i]))i++;
        else visch[getc(s,i)]=0,i+=2;
    return res;
}
string ans;
int pid,length;
vector<string>a[30],tmpa[30];
void initval(){
	if(lv==M1)return;
	for(int i=0;i<30;i++)
		a[i].clear();
    for(int i=0;i<N;i++){
        if(!vis[i])continue;
        int l=0,r,sz=p[i].size();
        while(l<sz){
            while(l<sz&&split(p[i].co[l]))l++;
            r=l;
            while(r<sz&&!split(p[i].co[r]))r++;
            r--;
            if(l<=r)a[(r-l+1)/2].push_back(p[i].get(l));
            l=r+1;
        }
    }
    // for(int i=0;i<65536;i++)
    //     if(fv[i]){
    //         string s="";
    //         s+=(unsigned char)(i/256),s+=(unsigned char)(i%256);
    //         a[1].push_back(s);
    //     }
    for(int i=0;i<30;i++)
        sort(a[i].begin(),a[i].end(),[&](const string&x,const string&y){
            return getval(x)>getval(y);
        });
    // freopen("out.txt","w",stdout);
    // for(int i=0;i<30;i++)
    //     for(auto s:a[i])
    //         cout<<s<<' '<<getval(s)<<endl;
}
void setting(){
	printf("请选择诗词难度 (1-%d): ",M1);
	lv=read();
	if(lv<1||lv>M1){
		puts("难度错误");
		system("pause");
		exit(0);
	}
	if(lv!=M1){
		printf("请选择猜测难度 (1-%d): ",M2);
		hd=read();
		if(hd<1||hd>M2){
			puts("难度错误");
			system("pause");
			exit(0);
		}
	}
	memset(vis,0,sizeof(vis));
	if(lv!=M1){
		for(int i=1;i<=lv;i++){
			freopen(Filelevel(i).c_str(),"r",stdin);
			while(1){
				string s=reads();
				if(s[0]=='<')break;
				vis[sti(s)]=1;
			}
		}
	}
	else memset(vis,1,sizeof(vis));
	freopen("CON","r",stdin);
    initval();
}
void load(){
	freopen("poetry.csv","r",stdin);
	for(int i=0;i<N;i++)
		p[i].read();
	for(int i=0;i<N;i++)
		if(p[i].check())p[i].init();
	puts("初始化完成");
	freopen("CON","r",stdin);
	setting();
}
const double hdi[M2+1][2]={
	{0,0},
	{0,0.33},
	{0,0.67},
	{0,1},
	{0.33,1},
	{0.67,1}
};
bool okans(const string&s){
	// cout<<s<<endl;
	if(length&&(int)s.size()!=length*2)return 0;
	if(lv==M1)return 1;
	// cout<<getval(s)<<endl;
	int sz=(int)a[s.size()/2].size(),l=0,r=sz-1,res=-1;
	// cout<<l<<' '<<r<<endl;
	while(l<=r){
		int mid=(l+r)>>1;
		// cout<<mid<<' '<<a[s.size()/2][mid]<<' '<<getval(a[s.size()/2][mid])<<endl;
		if(getval(a[s.size()/2][mid])==getval(s)){
			res=mid;
			break;
		}
		if(getval(a[s.size()/2][mid])>getval(s))l=mid+1;
		else r=mid-1;
	}
	// cout<<res<<endl;
	assert(res!=-1);
	// cout<<int(hdi[hd][0]*sz)<<' '<<int(hdi[hd][1]*sz+1)<<endl;
	if(res>=int(hdi[hd][0]*sz)&&res<=int(hdi[hd][1]*sz+1))return 1;
	return 0;
}
string getans(){
	pid=rad(0,N-1);
	while(!vis[pid]||!p[pid].check())pid=rad(0,N-1);
	string res=p[pid].get();
	if(okans(res))return res;
	return getans();
}
void game(){
	ans=getans();
	int siz=ans.size(),len=siz/2,cnt=0,maxcnt=20,ok=0,ok2=0;
	printf("题目生成完成，字数为 %d，请开始猜测，输入 q 投降并查看答案\n",len);
	map<pair<char,char>,bool>mp;
	for(int i=0;i<siz;i+=2)
		mp[make_pair(ans[i],ans[i+1])]=1;
	while(cnt<maxcnt){
		string guess=reads();
		if(guess=="q")break;
		if(((int)guess.size())!=siz||!findout(guess)){
			puts("无效猜测");
			continue;
		}
		ok=0,cnt++;
		for(int i=0;i<siz;i+=2){
			if(guess[i]==ans[i]&&guess[i+1]==ans[i+1])col(0,10),ok++,ok2++;
			else if(mp.find(make_pair(guess[i],guess[i+1]))!=mp.end())col(0,14),ok2++;
			else col(0,7);
			printf("██");
		}
		col(0,7);
		printf("(%d/%d)\n",cnt,maxcnt);
		if(cnt==10&&ok2==0){
			int x=rad(0,len-1);
			string ht="";
			ht+=ans[x*2],ht+=ans[x*2+1];
			printf("提示：答案中包含“%s”\n",ht.c_str());
		}
		if(ok==len)break;
	}
	if(ok==len)printf("恭喜你猜对了，猜测次数为 %d\n",cnt);
	else printf("你没有猜出答案，答案是“%s”\n",ans.c_str());
}
void start(){
	while(1){
		puts("输入 r 开始游戏，输入 q 退出程序，输入 s 设置难度，输入一个正整数限定字数，输入 0 取消限定");
		while(1){
			string op=reads();
			if(op=="r")break;
			else if(op=="q")return;
			else if(op=="s"){
				setting();
				continue;
			}
			else if(isnum(op)){
				int x=sti(op);
				if(x==0){
					printf("已取消限定字数\n");
					length=0;
					continue;
				}
				if(a[x].empty()){
					printf("没有字数为 %d 的诗词\n",x);
					continue;
				}
				printf("已设置字数为 %d\n",x);
				length=x;
				continue;
			}
			else puts("无效输入");
		}
		game();
	}
}
signed main(){
	load();
	start();
	return 0;
}