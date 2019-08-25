#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

class BigInt{
    bool positive = false;

    public:
    string string_int;

    vector<int> vec;

    void setInt(string s){
        int flag = 0;

        try{
            if(s[0] == '-'){
                for(int i=1;i<s.length();i++){
                    int ascii = s[i]-48;

                    if(ascii <0  || ascii>9){
                        flag = 1;
                        throw s;
                    }
                }
                positive = true;
            }
            else{
                for(int i=0;i<s.length();i++){
                    int ascii = s[i]-48;

                    if(ascii <0  || ascii>9){
                        flag = 1;
                        throw s;
                    }
                }
                positive = true;
            }
        }
        catch(string x){
            cout<<x<<endl;
            cout<<"Not an Integer"<<endl;
        }
        if(flag == 0){
            vec.clear();
            for(int i=0;i<s.length();i++){
                if(!positive){
                    continue; 
                }
                else{
                    
                    vec.push_back(s[i]-48);
                }
            }
            string_int = s;
        }
    }

    string getInt(){
        return string_int;
    }

    BigInt add(BigInt value){
        BigInt ans;
        vector<int> sum;

        reverse(this->vec.begin(), this->vec.end());
        reverse(value.vec.begin(), value.vec.end());

        int min_value = (this->vec.size() > value.vec.size()) ? value.vec.size() : this->vec.size();

        int carry = 0;
        int k = 0;
        if(this->positive & value.positive){
            for(int i=0;i<min_value;i++){
                int inter = this->vec.at(i)+value.vec.at(i)+carry;
                if(inter>=10){
                    sum.push_back(inter-10);
                    carry = 1;
                }
                else{
                    sum.push_back(inter);
                    carry = 0;
                }
                k++;
            }

            if(this->vec.size() > value.vec.size()){
                for(int j=k;j<this->vec.size();j++){
                    int inter = this->vec.at(j) + carry;
                    if(inter>=10){
                        sum.push_back(inter-10);
                        carry = 1;
                    }
                    else{
                        sum.push_back(inter);
                        carry = 0;
                    }
                }
            }

            if(this->vec.size() < value.vec.size()){
                for(int j=k;j<value.vec.size();j++){
                    int inter = value.vec.at(j) + carry;
                    if(inter>=10){
                        sum.push_back(inter-10);
                        carry = 1;
                    }
                    else{
                        sum.push_back(inter);
                        carry = 0;
                    }
                }
            }

            if(carry == 1){
                sum.push_back(1);
                carry = 0;
            }
        }
               

        string s;

        reverse(sum.begin(), sum.end());
        for(int i=0;i<sum.size();i++){
            s += (sum[i]+48); 
        }

        ans.setInt(s);
        return ans;
    }
    BigInt mul(BigInt value){

        BigInt ans_mul;
        
        int len1 = this->vec.size();
        int len2 = value.vec.size();

        vector<int> result(len1+len2, 0);
        int i_n1 = 0;
        int i_n2 = 0;

        //cout<<"here"<<endl;
        for(int i=len1-1;i>=0;i--){
            int carry = 0;
            int n1 = this->vec.at(i);

            i_n2 = 0;
            //cout<<"here1"<<endl;
            for(int j = len2-1;j>=0;j--){
                int n2 = value.vec.at(j);
                //cout<<"here2"<<endl;
                int sum = n1*n2 + result[i_n1+i_n2] + carry;

                carry = sum/10;
                
                //cout<<"here3"<<endl;
                //result.insert (result.begin()+i_n1+i_n2, sum%10);
                 result[i_n1 + i_n2] = sum%10;
                 //cout<<result[i_n1+i_n2]<<endl;

                i_n2++;
            }

            if(carry>0){
                result[i_n1 + i_n2] += carry;
                //result.insert(result.begin()+i_n1+i_n2, carry+result[i_n1+i_n2]);
            }

            i_n1++;
        }
        int i = result.size() - 1;
        while(i>=0 && result[i] == 0){
            i--;
        }
        if(i == -1)
            ans_mul.setInt("0");

        string s = "";
        while(i>=0){
            s += std::to_string(result[i--]);
        }
        ans_mul.setInt(s);
        return ans_mul;
    }
    BigInt max(BigInt value){
        int len1 = this->vec.size();
        int len2 = value.vec.size();


        BigInt maximum;
        if(len1 > len2)
            return *this;
        else if(len2 > len1){
            maximum.setInt(value.string_int);
            return maximum;
        }
        else{
            for(int i=0;i<len1;i++){
                if(this->vec.at(i) > value.vec.at(i))
                    return *this;
                else if(this->vec.at(i) < value.vec.at(i))
                    return value;
            }
            return value;
        }
    }

    BigInt min(BigInt value){
        int len1 = this->vec.size();
        int len2 = value.vec.size();


        BigInt minimum;
        if(len1 < len2)
            return *this;
        else if(len2 < len1){
            minimum.setInt(value.string_int);
            return minimum;
        }
        else{
            for(int i=0;i<len1;i++){
                if(this->vec.at(i) < value.vec.at(i))
                    return *this;
                else if(this->vec.at(i) > value.vec.at(i))
                    return value;
            }
            return *this;
        }
    }

    BigInt sub(BigInt value){
        this->trims();
        value.trims();
        BigInt value1 = *this;
        BigInt value2 = value;

        string str = "";

        int n1 = value1.vec.size();
        int n2 = value2.vec.size();

        reverse(value1.vec.begin(), value1.vec.end());
        reverse(value2.vec.begin(), value2.vec.end());

        int carry = 0;
        for(int i=0;i<n2;i++){
            int substract = ((value1.vec[i])-(value2.vec[i])-carry);
            if(substract<0){
                substract+=10;
                carry=1;
            }
            else{
                carry=0;
            }

            str.push_back(substract + '0');
        }

        for(int i=n2;i<n1;i++){
            int substract = ((value1.vec[i])-carry);

            if(substract<0){
                substract+=10;
                carry=1;
            }
            else
                carry=0;

            str.push_back(substract+'0');
        }

        reverse(str.begin(), str.end());

        BigInt ans;
        ans.setInt(str);
        return ans;

    }
    bool allZero(vector<int> zero){
        for(int i: zero){
            if(i!=0){
                return false;
            }
        }
        return true;
    }

    bool checkAllZero(string s){
        for(int i=0;i<s.length();i++){
            if(s[i] != '0')
                return false;
        }
        return true;
    }

    bool checkEqual(string s1, string s2){
        int len1 = s1.length();
        int len2 = s2.length();
        if(len1 != len2)
            return false;
        else{
            for(int i=0;i<len1;i++){
                if(s1[i] != s2[i])
                    return false;
            }
            return true;
        }
    }
    BigInt factorial(){
        bool val = allZero(this->vec);
        BigInt fact = *this;
        BigInt minus_one;
        minus_one.setInt("1");
        BigInt ans;
        ans.setInt("1");
        while(!val){
            ans = ans.mul(fact);
            // cout<<ans.getInt()<<endl;
            val = allZero(fact.vec);
            // cout<<val<<endl;
            fact = fact.sub(minus_one);
            // cout<<fact.getInt()<<endl;
            if(checkAllZero(fact.string_int))
                break;
        }
        return ans;
    }

    bool isGreater(BigInt value){

        this->trims();
        value.trims();
        int len1 = this->string_int.length();
        int len2 = value.string_int.length();
        int index_i=0;
        int index_j=0;

        if(len1 > len2){
            return true;
        }
        else if(len1 < len2)
            return false;
        else{
            for(int i=0;i<len1;i++){
                if(this->string_int[i] - '0' > value.string_int[i] - '0')
                    return true;
                else if(this->string_int[i] - '0' < value.string_int[i] - '0')
                    return false;
            }
            return false;
        }
    }
    void trims(){
        int len1 = this->string_int.length();
        // cout<<"Therer you go"<<this->string_int<<endl;
        string s;
        int index;
        for(int i=0;i<len1;i++){
            if(this->string_int[i]!='0'){
                index = i;
                break;
            }
        }
        for(int i=0;i<len1;i++){
            if(index>i)
                continue;
            else{
                s += this->string_int[i];
            }
        }
        // cout<<s<<endl;
        this->setInt(s);
        // cout<<this->string_int<<endl;
    }

    BigInt division(int value){
        int len = this->string_int.length();
        int index = 0;
        string ans = "";
        int remainder = 0;
        while(index < len){
            int val = (remainder*10) + (this->string_int[index] - '0');
            if( val%2 == 1){
                remainder = 1;
                ans += (val/2+48);
            }
            else{
                remainder = 0;
                ans += (val/2+48);
            }
            index++;
        }
        BigInt result;
        result.setInt(ans);
        return result;
    }

    bool isOdd(string number){
        int len1 = number.length();
        int value = number[len1-1] - 48;
        // cout<<"last_digit = "<<value<<endl;
        if(value%2!=0)
            return true;
        else
            false;
    }
    BigInt GCD(BigInt value){
        // if(checkAllZero(this->string_int))
        //     return value;
        // if(checkAllZero(value.string_int))
        //     return *this;
        // if(checkEqual(this->string_int, value.string_int))
        //     return value;
        // if(this->isGreater(value)){
        //     *this = this->sub(value);
        //     this->trims();
        //     return this->GCD(value);   
        // }
        // if(value.isGreater(*this)){
        //     value = value.sub(*this);
        //     value.trims();
        //     return value.GCD(*this);
        // }

        while(!checkEqual(this->string_int, value.string_int)){
            // cout<<this->string_int<< value.string_int<<endl;
            if(this->isGreater(value)){
                *this = this->sub(value);
            }
            else{
                value = value.sub(*this);
            }
        }

        return *this;
    }



    BigInt exponent(BigInt power){
        BigInt res;
        res.setInt("1");

        BigInt value1;
        value1.setInt("0");

        while(power.isGreater(value1)){

            if(isOdd(power.string_int)){
                res = res.mul(*this);
            }
            *this = this->mul(*this);
            power = power.division(2);
        }
        return res;  
    }

};

std::ostream& operator<<(std::ostream &strm, const BigInt &a) {
  return strm  << a.string_int ;
}