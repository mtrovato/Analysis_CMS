#include "../interface/TCMET.h"
#include "../interface/TCMETLinkDef.h"
#include <iostream>

TCMET::TCMET() {}

TCMET::~TCMET() {}

// "get" methods ------------------------------------

float TCMET::SumEt() const {
  return _sumEt;
}

float TCMET::MuonFraction() const {
  return _muonFraction;
}

float TCMET::NeutralHadronFraction() const {
  return _neutralHadronFraction;
}

float TCMET::NeutralEMFraction() const {
  return _neutralEMFraction;
}

float TCMET::ChargedHadronFraction() const {
  return _chargedHadronFraction;
}

float TCMET::ChargedEMFraction() const {
  return _chargedEMFraction;
}

float TCMET::UnCorPhi() const {
  return _unCorPhi;
}
    // "set" methods ---------

void TCMET::SetSumEt(float n) {
  _sumEt = n;
}

void TCMET::SetMuonFraction(float n) {
  _muonFraction = n;
}

void TCMET::SetNeutralHadronFraction(float n) {
  _neutralHadronFraction = n;
}

void TCMET::SetNeutralEMFraction(float n) {
  _neutralEMFraction = n;
}

void TCMET::SetChargedHadronFraction(float n) {
  _chargedHadronFraction = n;
}

void TCMET::SetChargedEMFraction(float n) {
  _chargedEMFraction = n;
}

void TCMET::SetUnCorPhi(float n) {
  _unCorPhi = n;
}
