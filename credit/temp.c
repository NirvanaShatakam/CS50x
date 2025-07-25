do
    {
        double temp1 = temp;
        float one = temp1 / 10;
        int d1 = (one - floor(one))*10;
        printf("%i", d1);
        temp1 = floor(one)*10;
    } while(temp1 != 0)
