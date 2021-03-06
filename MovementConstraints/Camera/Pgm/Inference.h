/*
	Copyright (c) 2015,	TAPAS Team:
	-Jan Wietrzykowski (jan.wietrzykowski@cie.put.poznan.pl).
	Poznan University of Technology
	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice,
	this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
	this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
	AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef INFERENCE_H_
#define INFERENCE_H_

#include <vector>

#include "../Pgm/Pgm.h"

class Inference{

public:
	struct InfEdge{
		int i, j;
		int w;
		InfEdge() {}
		InfEdge(int ii, int ij, int iw) : i(ii), j(ij), w(iw) {}
	};

private:

	//std::vector<double> marginalize(Cluster* cluster,
	//								const std::vector<RandVar*>& vars);

	/*std::vector<double> compSumProdMsg(Cluster* src,
										Cluster* dst,
										const std::vector<std::vector<double> >& inMsgs);

	std::vector<double> compMaxSumMsg(Cluster* src,
										Cluster* dst,
										const std::vector<std::vector<double> >& inMsgs);*/

	static std::vector<double> compCurMarginal(Cluster* clust,
										MargType type,
										const std::vector<std::vector<double> >& inMsgs,
										const std::vector<double>& params,
										const std::vector<double>& obsVec = std::vector<double>());

	static std::vector<int> selectMST(const std::vector<InfEdge>& edges, //weight sorted
								int numClusters);

	static void passMessage(const Pgm& pgm,
						MargType type,
						std::vector<std::vector<std::vector<double> > >& msgs,
						std::vector<std::vector<std::vector<double> > >& prevMsgs,
						Cluster* src,
						Cluster* dst,
						const std::vector<double>& params,
						const std::vector<double>& obsVec = std::vector<double>());

	static void treeReparametrize(const Pgm& pgm,
							MargType type,
							std::vector<std::vector<std::vector<double> > >& msgs,
							std::vector<std::vector<std::vector<double> > >& prevMsgs,
							const std::vector<InfEdge>& edges,
							const std::vector<int>& selEdges,
							const std::vector<double>& params,
							const std::vector<double>& obsVec = std::vector<double>());

	static bool runBP(const Pgm& pgm,
						MargType type,
						std::vector<std::vector<std::vector<double> > >& msgs,
						const std::vector<double>& params,
						const std::vector<double>& obsVec = std::vector<double>());

public:
	static std::vector<std::vector<double> > compMarginalsBF(const Pgm& pgm,
															double& logPartFunc,
															const std::vector<double>& params,
															const std::vector<double>& obsVec = std::vector<double>());

	static double compJointProbUnnorm(const Pgm& pgm,
									const std::vector<double>& vals,
									const std::vector<double>& params,
									const std::vector<double>& obsVec = std::vector<double>());

	static std::vector<std::vector<double> > compMarginalsParam(const Pgm& pgm,
													double& logPartFunc,
													std::vector<std::vector<std::vector<double> > >& msgs,
													const std::vector<double>& params,
													const std::vector<double>& obsVec = std::vector<double>());

	static std::vector<std::vector<double> > compMarginals(const Pgm& pgm,
													double& logPartFunc,
													std::vector<std::vector<std::vector<double> > >& msgs,
													const std::vector<double>& obsVec = std::vector<double>());

	static bool compMAPParam(const Pgm& pgm,
							std::vector<std::vector<double> >& marg,
							std::vector<std::vector<std::vector<double> > >& msgs,
							const std::vector<double>& params,
							const std::vector<double>& obsVec = std::vector<double>());

	static std::vector<std::vector<double> > decodeMAP(const Pgm& pgm,
														std::vector<std::vector<double> >& marg,
														std::vector<std::vector<std::vector<double> > >& msgs,
														const std::vector<double>& params,
														const std::vector<double>& obsVec = std::vector<double>());
};



#endif /* INFERENCE_H_ */
