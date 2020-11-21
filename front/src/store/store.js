import Vue from 'vue'
import Vuex from 'vuex'

import database from '@/store/modules/database'

Vue.use(Vuex)

const store = new Vuex.Store({
	modules: {
		database
	}
})

export default store
