import Vue from 'vue'
import Vuex from 'vuex'

import database from '@/store/modules/database'
import collection from '@/store/modules/collection'

Vue.use(Vuex)

const store = new Vuex.Store({
	modules: {
		database,
		collection,
	}
})

export default store
