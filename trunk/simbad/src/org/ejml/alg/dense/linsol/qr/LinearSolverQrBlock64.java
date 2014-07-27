/*
 * Copyright (c) 2009-2014, Peter Abeles. All Rights Reserved.
 *
 * This file is part of Efficient Java Matrix Library (EJML).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.ejml.alg.dense.linsol.qr;

import org.ejml.alg.block.linsol.qr.BlockQrHouseHolderSolver;
import org.ejml.alg.dense.linsol.LinearSolver_B64_to_D64;


/**
 * Wrapper around {@link BlockQrHouseHolderSolver} that allows it to process
 * {@link org.ejml.data.DenseMatrix64F}.
 *
 * @author Peter Abeles
 */
public class LinearSolverQrBlock64 extends LinearSolver_B64_to_D64 {

    public LinearSolverQrBlock64() {
        super(new BlockQrHouseHolderSolver());
    }
}
