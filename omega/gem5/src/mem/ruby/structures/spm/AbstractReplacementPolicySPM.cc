/*
 * Copyright (c) 2013 Advanced Micro Devices, Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Derek Hower
 */

#include "mem/ruby/structures/spm/AbstractReplacementPolicySPM.hh"

AbstractReplacementPolicySPM::AbstractReplacementPolicySPM(const Params * p)
  : SimObject(p)
{
    m_num_sets = p->size/p->block_size/p->assoc;
    m_assoc = p->assoc;
    m_freq_ref_ptr = new int*[m_num_sets];
    m_coll_ref_ptr = new int*[m_num_sets];
    for(unsigned i = 0; i < m_num_sets; i++){
        m_freq_ref_ptr[i] = new int[m_assoc];
        m_coll_ref_ptr[i] = new int[m_assoc];
        for(unsigned j = 0; j < m_assoc; j++){
            m_freq_ref_ptr[i][j] = 0;
            m_coll_ref_ptr[i][j] = 0;
        }
    }
}

AbstractReplacementPolicySPM *
ReplacementPolicySPMParams::create()
{
    fatal("Cannot create an AbstractReplacementPolicySPM");
    return NULL;
}



AbstractReplacementPolicySPM::~AbstractReplacementPolicySPM()
{
    if (m_freq_ref_ptr != NULL){
        for (unsigned i = 0; i < m_num_sets; i++){
            if (m_freq_ref_ptr[i] != NULL){
                delete[] m_freq_ref_ptr[i];
            }
        }
        delete[] m_freq_ref_ptr;
    }

    if (m_coll_ref_ptr != NULL){
        for (unsigned i = 0; i < m_num_sets; i++){
            if (m_coll_ref_ptr[i] != NULL){
                delete[] m_coll_ref_ptr[i];
            }
        }
        delete[] m_coll_ref_ptr;
    }

}

/**
*Abraham - adding source & destination scratchpads
*@todo - update the following line to reflect the freq - coll
*based replacement policy instead of lru
*/
int
AbstractReplacementPolicySPM::getLastAccess(int64_t set, int64_t way)
{
    return m_freq_ref_ptr[set][way];
}
