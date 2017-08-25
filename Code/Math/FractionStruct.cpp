struct​​ ​fraction 
{ 
​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​a​,​​ ​b​ ​​=​​ ​​1; 
 
​ ​​ ​​ ​​ ​fraction​ ​​operator​​ ​​+(​const​​ ​fraction​ ​​&​other) 
​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​fraction​ ​temp; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​g​ ​​=​​ ​gcd​(​this​->​b​,​​ ​other​.​b​); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​d​ ​​=​​ ​​this​->​b​/​g; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​denom​ ​​=​​ ​other​.​b​*​d; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​a​ ​​=​​ ​other​.​a​*​d​ ​​+​​ ​​this​->​a​*(​denom​/​this​->​b​); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​b​ ​​=​​ ​denom; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​simplify​(); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​return​​ ​temp; 
​ ​​ ​​ ​​ ​} 
 
​ ​​ ​​ ​​ ​fraction​ ​​operator​​ ​​*(​const​​ ​fraction​ ​​&​other) 
​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​fraction​ ​temp; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​a​ ​​=​​ ​​this​->​a​ ​​*​​ ​other​.​a; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​b​ ​​=​​ ​​this​->​b​ ​​*​​ ​other​.​b; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​simplify​(); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​return​​ ​temp; 
​ ​​ ​​ ​​ ​} 
 
​ ​​ ​​ ​​ ​fraction​ ​​operator​​ ​​/(​const​​ ​fraction​ ​​&​other) 
​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​fraction​ ​temp; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​a​ ​​=​​ ​​this​->​a​ ​​*​​ ​other​.​b; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​b​ ​​=​​ ​​this​->​b​ ​​*​​ ​other​.​a; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​simplify​(); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​return​​ ​temp; 
​ ​​ ​​ ​​ ​} 
 
​ ​​ ​​ ​​ ​fraction​ ​​operator​​ ​​-(​const​​ ​fraction​ ​​&​other) 
​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​fraction​ ​temp; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​g​ ​​=​​ ​gcd​(​this​->​b​,​​ ​other​.​b​); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​d​ ​​=​​ ​​this​->​b​/​g; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​denom​ ​​=​​ ​other​.​b​*​d; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​a​ ​​=​​ ​​this​->​a​*(​denom​/​this​->​b​)-​other​.​a​*​d​;​​ ​; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​b​ ​​=​​ ​denom; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​simplify​(); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​return​​ ​temp; 
​ ​​ ​​ ​​ ​} 
 
​ ​​ ​​ ​​ ​​bool​​ ​​operator​​ ​​>(​const​​ ​fraction​ ​​&​other) 
​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​fraction​ ​temp​ ​​=​​ ​​*​this​​ ​​-​​ ​other; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​temp​.​simplify​(); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​return​​ ​temp​.​a​ ​​>​​ ​​0; 
​ ​​ ​​ ​​ ​} 
 
​ ​​ ​​ ​​ ​​void​​ ​simplify​() 
​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​t1​ ​​=​​ ​abs​(​this​->​a​); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​long​​ ​​long​​ ​t2​ ​​=​​ ​abs​(​this​->​b​); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​if​(​t1​ ​​==​​ ​​0) 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​this​->​b​ ​​=​​ ​​1; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​return; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​} 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​int​​ ​g​ ​​=​​ ​gcd​(​t1​,​​ ​t2​); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​while​(​g​ ​​!=​​ ​​1) 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​t1​ ​​/=​​ ​g; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​t2​ ​​/=​​ ​g; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​g​ ​​=​​ ​gcd​(​t1​,​​ ​t2​); 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​} 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​if​((​this​->​a​ ​​<​​ ​​0​​ ​​and​​ ​​this​->​b​ ​​<​​ ​​0​)​​ ​​or​​ ​​(​this​->​a​ ​​>=​​ ​​0​​ ​​and​​ ​​this​->​b​ ​​>=​​ ​​0​)) 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​this​->​a​ ​​=​​ ​t1; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​this​->​b​ ​​=​​ ​t2; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​} 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​else 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​{ 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​this​->​a​ ​​=​​ ​​-​1​*​t1; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​​this​->​b​ ​​=​​ ​t2; 
​ ​​ ​​ ​​ ​​ ​​ ​​ ​​ ​} 
 
​ ​​ ​​ ​​ ​} 
}; 
 


    {
        fraction temp = *this - other;
        temp.simplify();
        return temp.a > 0;
    }

    void simplify()
    {
        long long t1 = abs(this->a);
        long long t2 = abs(this->b);
        if(t1 == 0)
        {
            this->b = 1;
            return;
        }
        int g = gcd(t1, t2);
        while(g != 1)
        {
            t1 /= g;
            t2 /= g;
            g = gcd(t1, t2);
        }
        if((this->a < 0 and this->b < 0) or (this->a >= 0 and this->b >= 0))
        {
            this->a = t1;
            this->b = t2;
        }
        else
        {
            this->a = -1*t1;
            this->b = t2;
        }

    }
};


