/*
 * Copyright 2009 Giesecke & Devrient GmbH.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.smartcard;

public class CardNotPresentException extends CardException {

	private static final long serialVersionUID = 1346879911706545215L;

	public CardNotPresentException(String message) {
		super(message);
	}

	public CardNotPresentException(String message, Throwable cause) {
		super(message, cause);
	}

	public CardNotPresentException(Throwable cause) {
		super(cause);
	}

}
