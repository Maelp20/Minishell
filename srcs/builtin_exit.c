/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:32:55 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/26 16:33:14 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

/* pour EXIT builtin :
	ATTENTION : la valeur de retour sera entre 0 et 255. exit doit tout nettoyer (free et close).
 */
