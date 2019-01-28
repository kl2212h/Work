/**
 *  @file   ExampleAlgorithms/ShowerJudgeAlgorithm.cc
 *
 *  @brief  Implementation of the cluster merging algorithm class.
 *
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "Pandora/AlgorithmTool.h"

#include "ExampleAlgorithms/LArClusterHelper.h"

#include "ExampleAlgorithms/ShowerJudgeAlgorithm.h"

#include<vector>


using namespace pandora;
using namespace std;
namespace example_content
{


ShowerJudgeAlgorithm::ShowerJudgeAlgorithm() 
{
}

StatusCode ShowerJudgeAlgorithm::Run()
{
    const ClusterList *pClusterList = NULL;

    if (m_inputClusterListName.empty())
    {
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pClusterList));
    }
    else
    {
        PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_INITIALIZED, !=, PandoraContentApi::GetList(*this, m_inputClusterListName, pClusterList));
    }

    if (!pClusterList || pClusterList->empty())
    {
        if (PandoraContentApi::GetSettings(*this)->ShouldDisplayAlgorithmInfo())
            cout << "ShowerJudgeAlgorithm: unable to find cluster list " << m_inputClusterListName << endl;

        return STATUS_CODE_SUCCESS;
    }

    ClusterVector unsortedVector, clusterVector;

    for (ClusterList::const_iterator iter = pClusterList->begin(), iterEnd = pClusterList->end(); iter != iterEnd; ++iter) clusterVector.push_back(*iter);

    cout<<"number of cluster="<<clusterVector.size()<<endl;

    pair<int, double> showerInfo;
    this->PopulateInformation(clusterVector, showerInfo);

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void ShowerJudgeAlgorithm::GetPreprocessedListOfClusters(ClusterVector &unsortedVector, ClusterVector &sortedVector) const
{
    for (const Cluster *const pSeedCluster : unsortedVector)
    {

}
    }
//------------------------------------------------------------------------------------------------------------------------------------------
void ShowerJudgeAlgorithm::PopulateInformation(ClusterVector &sortedVector, std::pair<int, double> showerInfo) const
{

    for (const Cluster *const pSeedCluster : sortedVector)
      {
	double TotalEnergy;
	double Length;
	CaloHitList allNewThreeDHits;
	
	const OrderedCaloHitList &orderedCaloHitList(pSeedCluster->GetOrderedCaloHitList());
	
	for (OrderedCaloHitList::const_iterator iter = orderedCaloHitList.begin(), iterEnd = orderedCaloHitList.end(); iter != iterEnd; ++iter)
	  {
	    for (CaloHitList::const_iterator hitIter = iter->second->begin(), hitIterEnd = iter->second->end(); hitIter != hitIterEnd; ++hitIter)
	      {
		TotalEnergy +=(*hitIter)->GetInputEnergy();
		allNewThreeDHits.push_back(*hitIter);
		Length=LArClusterHelper::GetLength(pSeedCluster);
	      }
	  }            
    cout<<"total energy="<<TotalEnergy<<"MeV" <<endl;
    cout<<"length="<<Length<<"cm"<<endl;
    cout<<"dE/dX="<<TotalEnergy/Length<<endl;
    cout<<"--------------------------------------------------------------------------------"<<endl;
      }
}
    
//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode ShowerJudgeAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "InputClusterListName", m_inputClusterListName));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content
