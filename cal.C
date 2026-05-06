#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void calibration()
{
    vector<TString> files = {
        "cal0_250ns.txt",
        "cal1_2us.txt",
        "cal2_6us.txt",
        "cal3_10us.txt",
        "cal4_14us.txt"};

    vector<double> oscil = {250, 2000, 6000, 10000, 14000};

    TH1F *h1[5];
    TH1F *h2[5];
    TH1F *h3[5];

    vector<double> means_1 = {};
    vector<double> means_2 = {};
    vector<double> means_3 = {};

    vector<double> std_1 = {};
    vector<double> std_2 = {};
    vector<double> std_3 = {};

    TCanvas *c[5];

    for (int i = 0; i < 5; ++i)
    {
        ifstream file(files[i].Data());

        int event;
        float time;

        string P1_hex, P2_hex, P3_hex;

        h1[i] = new TH1F(Form("h1_%d", i), "", 1000, 0, 4096);
        h2[i] = new TH1F(Form("h2_%d", i), "", 1000, 0, 4096);
        h3[i] = new TH1F(Form("h3_%d", i), "", 1000, 0, 4096);

        while (file >> event >> time >> P1_hex >> P2_hex >> P3_hex)
        {
            UInt_t P1 = stoul(P1_hex, nullptr, 16);
            UInt_t P2 = stoul(P2_hex, nullptr, 16);
            UInt_t P3 = stoul(P3_hex, nullptr, 16);

            h1[i]->Fill(P1);
            h2[i]->Fill(P2);
            h3[i]->Fill(P3);
        }

        means_1.push_back(h1[i]->GetMean());
        std_1.push_back(h1[i]->GetRMS());

        means_2.push_back(h2[i]->GetMean());
        std_2.push_back(h2[i]->GetRMS());

        means_3.push_back(h3[i]->GetMean());
        std_3.push_back(h3[i]->GetRMS());
    }

    TCanvas *c1 = new TCanvas();
    TGraphErrors *g1 = new TGraphErrors(5, oscil.data(), means_1.data(), nullptr, std_1.data());
    TF1 *f1 = new TF1("f1", "pol1", 0, 15000);
    g1->Draw();
    g1->Fit(f1, "R");
        TPaveText *legend_p1 = new TPaveText(0.60, 0.15, 0.88, 0.38, "NDC");
        legend_p1->SetFillColor(0);
        legend_p1->SetTextAlign(12);
        legend_p1->SetTextSize(0.04);
        legend_p1->SetBorderSize(0);
        legend_p1->AddText(Form("a = %.3f #pm %.3f", f1->GetParameter(1), f1->GetParError(1)));
        legend_p1->AddText(Form("b = %.4f #pm %.4f", f1->GetParameter(0), f1->GetParError(0)));
        legend_p1->AddText(Form("#chi^{2}/NDF = %.2f", f1->GetChisquare() / f1->GetNDF()));
        legend_p1->AddText(Form("NDF = %d", f1->GetNDF()));
        legend_p1->AddText(Form("Prob = %.4f", f1->GetProb()));
        legend_p1->Draw();

    TCanvas *c2 = new TCanvas();
    TGraphErrors *g2 = new TGraphErrors(5, oscil.data(), means_2.data(), nullptr,std_2.data());
    TF1 *f2 = new TF1("f2", "pol1", 0, 15000);
    g2->Draw();
    g2->Fit(f2, "R");
    TPaveText *legend_p2 = new TPaveText(0.60, 0.15, 0.88, 0.38, "NDC");
        legend_p2->SetFillColor(0);
        legend_p2->SetTextAlign(12);
        legend_p2->SetTextSize(0.04);
        legend_p2->SetBorderSize(0);
        legend_p2->AddText(Form("a = %.3f #pm %.3f", f2->GetParameter(1), f2->GetParError(1)));
        legend_p2->AddText(Form("b = %.4f #pm %.4f", f2->GetParameter(0), f2->GetParError(0)));
        legend_p2->AddText(Form("#chi^{2}/NDF = %.2f", f2->GetChisquare() / f2->GetNDF()));
        legend_p2->AddText(Form("Prob = %.4f", f2->GetProb()));
        legend_p2->Draw();

    TCanvas *c3 = new TCanvas();
    TGraphErrors *g3 = new TGraphErrors(5, oscil.data(), means_3.data(),nullptr, std_3.data());
    TF1 *f3 = new TF1("f3", "pol1", 0, 15000);
    g3->Draw();
    g3->Fit(f3, "R");
    TPaveText *legend_p3 = new TPaveText(0.60, 0.15, 0.88, 0.38, "NDC");
        legend_p3->SetFillColor(0);
        legend_p3->SetTextAlign(12);
        legend_p3->SetTextSize(0.04);
        legend_p3->SetBorderSize(0);
        legend_p3->AddText(Form("a = %.3f #pm %.3f", f3->GetParameter(1), f3->GetParError(1)));
        legend_p3->AddText(Form("b = %.4f #pm %.4f", f3->GetParameter(0), f3->GetParError(0)));
        legend_p3->AddText(Form("#chi^{2}/NDF = %.2f", f3->GetChisquare() / f3->GetNDF()));
        legend_p3->AddText(Form("Prob = %.4f", f3->GetProb()));
        legend_p3->Draw();

}