class Solution {
public:
	vector<string> subdomainVisits(vector<string>& cpdomains) {
		map<string, int> M;
		for (int i = 0; i < cpdomains.size(); i++)
		{
			string s = cpdomains[i];
			int times = stoi(s.substr(0, s.find(' ')));
			s = s.substr(s.find(' ') + 1);
			M[s] += times;
			while (s.find('.') != string::npos)
			{
				s = s.substr(s.find('.') + 1);
				M[s] += times;
			}
		}
		vector<string> ans;
		for (map<string, int>::iterator it = M.begin(); it != M.end(); it++)
		{
			ans.push_back(to_string(it->second) + ' ' + it->first);
		}
		return ans;
	}
};
