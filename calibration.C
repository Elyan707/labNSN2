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

    TH2F *h_P1 = new TH2F("h_P1", "", 4096, 0, 15000, 4096, 0, 4096);
    TH2F *h_P2 = new TH2F("h_P2", "", 4096, 0, 15000, 4096, 0, 4096);
    TH2F *h_P3 = new TH2F("h_P3", "", 4096, 0, 15000, 4096, 0, 4096);

    for (int i = 0; i < 5; ++i)
    {
        ifstream file(files[i].Data());

        int event;
        float time;

        string P1_hex, P2_hex, P3_hex;

        while (file >> event >> time >> P1_hex >> P2_hex >> P3_hex)
        {
            UInt_t  P1 = stoul(P1_hex, nullptr, 16);
            UInt_t  P2 = stoul(P2_hex, nullptr, 16);
            UInt_t  P3 = stoul(P3_hex, nullptr, 16);

            h_P1->Fill(oscil[i], P1);
            h_P2->Fill(oscil[i], P2);
            h_P3->Fill(oscil[i], P3);
        }
    }
    
    TProfile *p_P1 = h_P1->ProfileX();
    TProfile *p_P2 = h_P2->ProfileX();
    TProfile *p_P3 = h_P3->ProfileX();

    TF1 *f1 = new TF1("f1", "pol1", 0, 15000);
    TF1 *f2 = new TF1("f2", "pol1", 0, 15000);
    TF1 *f3 = new TF1("f3", "pol1", 0, 15000);
    
    TCanvas *c1 = new TCanvas("c_1", "histo 1", 900, 600);
    h_P1->Draw("COLZ");
    TCanvas *c2 = new TCanvas("c_2", "histo 2", 900, 600);
    h_P2->Draw("COLZ");
    TCanvas *c3 = new TCanvas("c_3", "histo 3", 900, 600);
    h_P3->Draw("COLZ");

    TCanvas *c_P1 = new TCanvas("c_P1", "profile 1", 900, 600);
    p_P1->GetXaxis()->SetTitle("Oscilloscope (ns)");
    p_P1->GetYaxis()->SetTitle("FPGA (TDC)");
    p_P1->SetMarkerStyle(20);
    p_P1->SetMarkerSize(1.2);
    p_P1->SetMarkerColor(kBlue+2);
    p_P1->SetLineColor(kBlack);

    p_P1->Draw("PE");
    p_P1->Fit(f1, "QR");

    TPaveText *legend_p1 = new TPaveText(0.60, 0.15, 0.88, 0.38, "NDC");
    legend_p1->SetFillColor(0);
    legend_p1->SetTextAlign(12);
    legend_p1->SetTextSize(0.04);
    legend_p1->SetBorderSize(0);
    legend_p1->AddText(Form("a = %.2f #pm %.2f",f1->GetParameter(1),f1->GetParError(1)));
    legend_p1->AddText(Form("b = %.2f #pm %.2f",f1->GetParameter(0),f1->GetParError(0)));
    legend_p1->AddText(Form("#chi^{2}/NDF = %.2f",f1->GetChisquare() / f1->GetNDF()));
    legend_p1->AddText(Form("NDF = %d", f1->GetNDF()));
    legend_p1->AddText(Form("Prob = %.4f", f1->GetProb()));
    legend_p1->Draw();

    TCanvas *c_P2 = new TCanvas("c_P2", "profile 2", 900, 600);
    p_P2->GetXaxis()->SetTitle("Oscilloscope (ns)");
    p_P2->GetYaxis()->SetTitle("FPGA (TDC)");
    p_P2->SetMarkerStyle(20);
    p_P2->SetMarkerSize(1.2);
    p_P2->SetMarkerColor(kBlue+2);
    p_P2->SetLineColor(kBlack);

    p_P2->Draw("PE");
    p_P2->Fit(f2, "QR");

    TPaveText *legend_p2 = new TPaveText(0.60, 0.15, 0.88, 0.38, "NDC");
    legend_p2->SetFillColor(0);
    legend_p2->SetTextAlign(12);
    legend_p2->SetTextSize(0.04);
    legend_p2->SetBorderSize(0);
    legend_p2->AddText(Form("a = %.2f #pm %.2f",f2->GetParameter(1),f2->GetParError(1)));
    legend_p2->AddText(Form("b = %.2f #pm %.2f",f2->GetParameter(0),f2->GetParError(0)));
    legend_p2->AddText(Form("#chi^{2}/NDF = %.2f",f2->GetChisquare() / f2->GetNDF()));
    legend_p2->AddText(Form("Prob = %.4f", f2->GetProb()));
    legend_p2->Draw();

    TCanvas *c_P3 = new TCanvas("c_P3", "profile 3", 900, 600);
    p_P3->GetXaxis()->SetTitle("Oscilloscope (ns)");
    p_P3->GetYaxis()->SetTitle("FPGA (TDC)");
    p_P3->SetMarkerStyle(20);
    p_P3->SetMarkerSize(1.2);
    p_P3->SetMarkerColor(kBlue+2);
    p_P3->SetLineColor(kBlack);

    p_P3->Draw("PE");
    p_P3->Fit(f3, "QR");

    TPaveText *legend_p3 = new TPaveText(0.60, 0.15, 0.88, 0.38, "NDC");
    legend_p3->SetFillColor(0);
    legend_p3->SetTextAlign(12);
    legend_p3->SetTextSize(0.04);
    legend_p3->SetBorderSize(0);
    legend_p3->AddText(Form("a = %.2f #pm %.2f",f3->GetParameter(1),f3->GetParError(1)));
    legend_p3->AddText(Form("b = %.2f #pm %.2f",f3->GetParameter(0),f3->GetParError(0)));
    legend_p3->AddText(Form("#chi^{2}/NDF = %.2f",f3->GetChisquare() / f3->GetNDF()));
    legend_p3->AddText(Form("Prob = %.4f", f3->GetProb()));
    legend_p3->Draw();
}