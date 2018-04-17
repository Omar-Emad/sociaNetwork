
int main()
{
    file ftest;
    ftest.setFileName("d:\\data\\users.txt");
    ftest.writeLine("1,omar,m,25");
	ftest.writeLine("2,ahmed,p,29");
    cout << ftest.readLine(0, "1");
    return 0;
}
