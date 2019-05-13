/*
 * fifo.h
 *
 *  Created on: Mar 2, 2019
 *      Author: bear
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdint.h"
#include "stdio.h"

template <size_t len, typename type> class TFifo {
	type fifo[len];

public:
	/// Конструктор.
	TFifo() {
		head = 0;
		size = 0;
	}

	/**	Добавить значение в очередь.
	 *
	 * 	@param[in] var Значение.
	 * 	@return False - если очередь заполнена, иначе true.
	 */
	bool push(type var) {
		if (size < len) {
			fifo[(head + size++) % len] = var;
			return true;
		}

		return false;;
	}

	/**	Достать переменную из очереди.
	 *
	 *	@param[out] Значение.
	 *	@return False - если очередь пуста, иначе true.
	 */
	bool pop(type &var) {
		if (size > 0) {
			var = fifo[head];
			head = (head + 1) % len;
			size--;
			return true;
		}

		return false;
	}

	///	Очистка очереди.
	void flush() {
		size =0;
	}

public:
	/// Начало очереди.
	size_t head;

	/// Конец очереди.
	size_t size;
};



#endif /* FIFO_H_ */
