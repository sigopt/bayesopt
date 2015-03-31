/*
-------------------------------------------------------------------------
   This file is part of BayesOpt, an efficient C++ library for 
   Bayesian optimization.

   Copyright (C) 2011-2014 Ruben Martinez-Cantin <rmcantin@unizar.es>
 
   BayesOpt is free software: you can redistribute it and/or modify it 
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   BayesOpt is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with BayesOpt.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------
*/

#include "bopt_state.hpp"
#include "fileparser.hpp"

#include <fstream>
#include <iostream>

namespace bayesopt
{       
    BOptState::BOptState(){
        mParameters = initialize_parameters_to_default();
    }
    
    void BOptState::saveToFile(std::string filename){
        utils::FileParser fp(filename);
        fp.openOutput();
        loadOrSave(fp);
    }
    
    void BOptState::loadFromFile(std::string filename){
        utils::FileParser fp(filename);
        fp.openInput();
        loadOrSave(fp);
    }
    
    void BOptState::loadOrSave(utils::FileParser &fp){     
        fp.readOrWrite("mCurrentIter", mCurrentIter);
        fp.readOrWrite("mCounterStuck", mCounterStuck);
        fp.readOrWrite("mYPrev", mYPrev);
        
        fp.readOrWrite("mParameters.n_iterations", mParameters.n_iterations);
        fp.readOrWrite("mParameters.n_inner_iterations", mParameters.n_inner_iterations);
        fp.readOrWrite("mParameters.n_init_samples", mParameters.n_init_samples);
        fp.readOrWrite("mParameters.n_iter_relearn", mParameters.n_iter_relearn);
        fp.readOrWrite("mParameters.init_method", mParameters.init_method);
        fp.readOrWrite("mParameters.random_seed", mParameters.random_seed);
        // Not necessary fields: verbose_level, log_filename, load_save_flag, load_filename, save_filename.
        fp.readOrWrite("mParameters.surr_name", mParameters.surr_name);
        fp.readOrWrite("mParameters.sigma_s", mParameters.sigma_s);
        fp.readOrWrite("mParameters.noise", mParameters.noise);
        fp.readOrWrite("mParameters.alpha", mParameters.alpha);
        fp.readOrWrite("mParameters.beta", mParameters.beta);
        
        // Enums
        if(fp.isReading()){
            mParameters.sc_type = str2score(fp.read("mParameters.sc_type").c_str());
            mParameters.l_type = str2learn(fp.read("mParameters.l_type").c_str());
        }
        else if(fp.isWriting()){
            fp.write("mParameters.sc_type",score2str(mParameters.sc_type));
            fp.write("mParameters.l_type", learn2str(mParameters.l_type));
        }
        
        fp.readOrWrite("mParameters.l_all", mParameters.l_all);
        fp.readOrWrite("mParameters.epsilon", mParameters.epsilon);
        fp.readOrWrite("mParameters.force_jump", mParameters.force_jump);
        
        fp.readOrWrite("mParameters.kernel.name", mParameters.kernel.name);
        fp.readOrWrite("mParameters.kernel.n_hp", mParameters.kernel.n_hp);
        fp.readOrWrite("mParameters.kernel.hp_mean", mParameters.kernel.hp_mean, mParameters.kernel.n_hp);
        fp.readOrWrite("mParameters.kernel.hp_std", mParameters.kernel.hp_std, mParameters.kernel.n_hp);
        
        fp.readOrWrite("mParameters.mean.name", mParameters.mean.name);
        fp.readOrWrite("mParameters.mean.n_coef", mParameters.mean.n_coef);
        fp.readOrWrite("mParameters.mean.coef_mean", mParameters.mean.coef_mean, mParameters.mean.n_coef);
        fp.readOrWrite("mParameters.mean.coef_std", mParameters.mean.coef_std, mParameters.mean.n_coef);
        
        fp.readOrWrite("mParameters.crit_name", mParameters.crit_name);
        fp.readOrWrite("mParameters.n_crit_params", mParameters.n_crit_params);
        fp.readOrWrite("mParameters.crit_params", mParameters.crit_params, mParameters.n_crit_params);
        
        fp.readOrWrite("mY", mY);
        fp.readOrWrite("mX", mX);
    } 
} //namespace bayesopt
