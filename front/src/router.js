import Vue from 'vue'
import Router from 'vue-router'

import store from '@/store/store'

import Home from '@/components/Home'

Vue.use(Router)

const router = new Router ({
	mode: 'history',
	base: process.env.BASE_URL,
	routes: [
		{
			path: '/',
			name: 'home',
			component: Home,
			meta: {
				title: 'Home'
			}
		}
	],
	parseQuery (query) {
		return qs.parse(query);
	},
	stringifyQuery (query) {
		let result = qs.stringify(query, {encode: false});

		return result ? ('?' + result) : '';
	}
})

export default router
